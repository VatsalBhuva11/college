import json
import os
import torch
import numpy as np


class Agent:
    def __init__(self, env):
        param_dir = 'Simulation/Utils/'
        with open(param_dir + 'config.json', 'r') as file:
            self.params = json.load(file)
        self.model_save_path = self.params['DATA_DIR'] + self.params['MAZE_MODEL_DIR']
        if not os.path.exists(self.model_save_path):
            os.makedirs(self.model_save_path)

        self.env = env
        self.position = None
        self.radius = self.params['RADIUS']
        self.model_name = None
        self.model = None
        self.state_size = self.env.maze_size * self.env.maze_size
        self.action_size = self.params['ACTION_SIZE']
        self.batch_size = self.params['BATCH_SIZE']

        self.model_filename = None
        self.game_steps = 0

        if torch.cuda.is_available():
            self.device = torch.device("cuda")
            print(f'Info: GPU is available...')
        else:
            self.device = torch.device("cpu")
            print(f'Info: CPU is available...')

        self.visited_states = None
        self.max_no_progress_steps = 10
        self.no_progress_steps = 0
        self.last_distance_to_goal = None

    def move(self, direction):
        self.position += direction

    def reset(self):
        self.position = np.array(self.env.source)
        return self._get_state()

    def _get_state(self):
        agent_state_index = self.position[0] * self.env.maze_size + self.position[1]
        return agent_state_index

    def step(self, action):
        self.game_steps += 1
        self.visited_states = set()
        terminated, truncated, info = False, False, {'Success': False}
        direction = np.array((self.env.directions[action][0], self.env.directions[action][1]))
        new_position = [self.position[0] + direction[0], self.position[1] + direction[1]]
        if self.env.is_valid_position(new_position):
            self.move(direction)
            if np.array_equal(self.position, self.env.destination):
                reward = 5.0
                print(f'\nInfo: HURRAY!! Agent has reached its destination...')
                info['Success'] = True
                terminated = True
                self.game_steps = 0
            else:
                reward = 0.0
                if self.game_steps >= 75:
                    truncated = True
                    self.game_steps = 0
                else:
                    current_dist_to_goal = self.env.distance_to_goal(self.position)
                    '''if self.last_distance_to_goal is not None and current_dist_to_goal >= self.last_distance_to_goal:
                        self.no_progress_steps += 1
                        if self.no_progress_steps >= self.max_no_progress_steps:
                            reward -= 0.04
                    else:
                        reward += 0.10
                        self.no_progress_steps = 0
                    self.last_distance_to_goal = current_dist_to_goal'''

                    '''if tuple(self.position) not in self.visited_states:
                        reward += 0.05
                        self.visited_states.add(tuple(self.position))
                    else:
                        reward -= 0.09'''
        else:
            reward = -0.75
            terminated = True
            self.game_steps = 0

        return self._get_state(), reward, terminated, truncated, info

    def train_value_agent(self, episodes, render):
        print(f'Info: Agent Training has been started over the Maze Simulation...')
        print(f'-' * 147)
        self.model_filename = (self.model_name + '_' + str(self.env.maze_size) + 'x' + str(self.env.maze_size) + '_'
                               + str(episodes) + '_ep_final.pt')
        returns_per_episode = np.zeros(episodes)
        epsilon_history = np.zeros(episodes)
        steps_per_episode = np.zeros(episodes)
        training_error = np.zeros(episodes)

        time_steps, saved_model = 0, False
        for episode in range(episodes):
            state = self.reset()
            done, returns, step, success_status, loss = False, 0, 0, 0, 0.0
            while True:
                self.env.update_display(self) if render else None
                time_steps += 1

                if time_steps % self.model.update_rate == 0:
                    self.model.update_target_network()

                action = self.model.act(state)
                new_state, reward, terminated, truncated, info = self.step(action)

                self.model.remember(state, action, reward, new_state, terminated)

                state = new_state
                returns += reward
                step += 1
                done = terminated or truncated

                if info['Success']:
                    self.save_model(is_policy_model=False)
                    saved_model = True

                if done:
                    print(f"Episode {episode + 1}/{episodes} - Steps: {step}, Return: {returns:.2f}, Epsilon: "
                          f"{self.model.epsilon:.3f}, Loss: {loss:0.4f}")
                    break

                if len(self.model.replay_buffer.buffer) > self.batch_size:
                    loss = self.model.train(self.batch_size)
            self.model.epsilon = max(self.model.epsilon * self.model.epsilon_decay, self.model.epsilon_min)

            returns_per_episode[episode] = returns
            epsilon_history[episode] = self.model.epsilon
            steps_per_episode[episode] = step
            training_error[episode] = loss

        print(f'-' * 147)
        if not saved_model:
            self.save_model(is_policy_model=False)
        print(f'-' * 147)
        return [returns_per_episode, epsilon_history, training_error, steps_per_episode, None]

    def test_value_agent(self, episodes, render):
        print(f'Info: Testing of the Agent has been started over the Maze Simulation...')
        print(f'Info: Source: {self.env.source} Destination: {self.env.destination}')
        print(f'-' * 147)

        success_rate = np.zeros(episodes)
        if os.path.exists(self.model_save_path):
            file_path = self.model_save_path + self.model_filename
            if os.path.isfile(file_path):
                self.model.main_network.load_state_dict(torch.load(file_path, weights_only=True))
                print(f'Info: Saved model has been successfully loaded...')
                print(f'-' * 147)
            else:
                print(f'Exception: Model file is not exists. Unable to load saved model weight!!')
                exit(0)
        else:
            print(f'Exception: The Data directory is not exists. Unable to load saved model weight!!')
            exit(0)
        self.model.main_network.eval()

        for episode in range(episodes):
            state = self.reset()
            done, returns, step, success_status = False, 0, 0, 0
            while not done:
                self.env.update_display(self) if render else None
                with torch.no_grad():
                    action = self.model.main_network(self.model.encode_state(state).to(self.device)).argmax().item()

                new_state, reward, terminated, truncated, info = self.step(action)

                state = new_state
                step += 1
                done = terminated or truncated
                returns += reward

                if info['Success']:
                    success_status = 1
            print(f'Episode {episode + 1}/{episodes} - Steps: {step}, Return: {returns:.2f}')
            success_rate[episode] = success_status
        print(f'-' * 147)
        print(f'Info: Testing has been completed...')
        return [None, None, None, None, success_rate]

    def train_policy_agent(self, episodes, render):
        print(f'Info: Agent Training has been started over the Maze Simulation...')
        print(f'-' * 147)
        self.model_filename = (self.model_name + '_' + str(self.env.maze_size) + 'x' + str(self.env.maze_size) + '_'
                               + str(episodes) + '_ep_final.pt')

        returns_per_episode = np.zeros(episodes)
        steps_per_episode = np.zeros(episodes)
        training_error = np.zeros((episodes, 2))

        saved_model = False
        for episode in range(episodes):
            state = self.reset()
            done, returns, step, success_status, loss = False, 0, 0, 0, 0.0
            while True:
                self.env.update_display(self) if render else None
                action, log_prob = self.model.select_action(state)
                new_state, reward, terminated, truncated, info = self.step(action)

                self.model.trajectory.append(state, action, reward, log_prob)

                state = new_state
                returns += reward
                step += 1
                done = terminated or truncated

                if info['Success']:
                    self.save_model(is_policy_model=True)
                    saved_model = True

                if done:
                    returns_per_episode[episode] = returns
                    steps_per_episode[episode] = step
                    break

            policy_loss, value_loss = self.model.train()
            training_error[episode, 0] = policy_loss
            training_error[episode, 1] = value_loss
            self.model.trajectory.clear()
            print(f"Episode {episode + 1}/{episodes} - Steps: {step}, Return: {returns:.2f}, Loss: {policy_loss:0.4f}")

        print(f'-' * 147)
        if not saved_model:
            self.save_model(is_policy_model=True)
        return [returns_per_episode, None, training_error, steps_per_episode, None]

    def test_policy_agent(self, episodes, render):
        print(f'Info: Testing of the Agent has been started over the Maze Simulation...')
        print(f'Info: Source: {self.env.source} Destination: {self.env.destination}')
        print(f'-' * 147)

        success_rate = np.zeros(episodes)
        if os.path.exists(self.model_save_path):
            file_path = self.model_save_path + self.model_filename
            if os.path.isfile(file_path):
                self.model.policy_network.load_state_dict(torch.load(file_path, weights_only=False))
                print(f'Info: Saved model has been successfully loaded...')
                print(f'-' * 147)
            else:
                print(f'Exception: Model file does not exist. Unable to load saved model weight!!')
                exit(0)
        else:
            print(f'Exception: The Data directory does not exist. Unable to load saved model weight!!')
            exit(0)
        self.model.policy_network.eval()

        for episode in range(episodes):
            state = self.reset()
            done, returns, step, success_status = False, 0, 0, 0

            while not done:
                self.env.update_display(self) if render else None
                with torch.no_grad():
                    action_probs = self.model.policy_network(self.model.encode_state(state).to(self.device))
                    action = action_probs.argmax().item()
                new_state, reward, terminated, truncated, info = self.step(action)

                state = new_state
                step += 1
                done = terminated or truncated
                returns += reward

                if info['Success']:
                    success_status = 1
            print(f'Episode {episode + 1}/{episodes} - Steps: {step}, Return: {returns:.2f}')
            success_rate[episode] = success_status
        print(f'-' * 147)
        print(f'Info: Testing has been completed...')
        return [None, None, None, None, success_rate]

    def save_model(self, is_policy_model):
        if is_policy_model:
            torch.save(self.model.policy_network.state_dict(), self.model_save_path + self.model_filename)
        else:
            torch.save(self.model.main_network.state_dict(), self.model_save_path + self.model_filename)
        print(f'Info: The model has been saved...')
