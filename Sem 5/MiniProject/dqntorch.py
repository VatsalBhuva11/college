import json
import torch
from torch import nn
import torch.nn.functional as F
import numpy as np
from collections import deque


class ReplayBuffer:
    def __init__(self, capacity):
        self.buffer = deque([], maxlen=capacity)

    def append(self, experience):
        self.buffer.append(experience)

    def sample(self, batch_size):
        minibatch_indices = np.random.choice(len(self.buffer), batch_size, replace=False)
        minibatch = []
        for idx in minibatch_indices:
            state, action, reward, next_state, done = self.buffer[idx]
            minibatch.append((state, action, reward, next_state, done))
        return minibatch


class DQN(nn.Module):
    def __init__(self, state_size, action_size):
        super().__init__()
        self.layer1 = nn.Linear(state_size, 32)
        self.layer2 = nn.Linear(32, 16)
        self.layer3 = nn.Linear(16, action_size)

    def forward(self, x):
        x = F.relu(self.layer1(x))
        x = F.relu(self.layer2(x))
        x = self.layer3(x)
        return x


class DQNModel:
    def __init__(self, state_size, action_size, maze, device):
        param_dir = 'Simulation/Utils/'
        with open(param_dir + 'config.json', 'r') as file:
            self.params = json.load(file)

        self.state_size = state_size
        self.action_size = action_size
        self.device = device
        self.maze = maze
        self.buffer_size = self.params['BUFFER_SIZE']
        self.replay_buffer = ReplayBuffer(self.buffer_size)
        self.gamma = self.params['GAMMA']
        self.alpha = self.params['ALPHA']
        self.epsilon = self.params['EPSILON']
        self.epsilon_min = self.params['EPSILON_MIN']
        self.epsilon_decay = self.params['EPSILON_DECAY']
        self.update_rate = self.params['UPDATE_RATE']

        self.main_network = DQN(self.state_size, self.action_size).to(device=device)
        self.target_network = DQN(self.state_size, self.action_size).to(device=device)
        self.target_network.load_state_dict(self.main_network.state_dict())
        self.loss_fn = nn.MSELoss()
        self.optimizer = torch.optim.Adam(self.main_network.parameters(), lr=self.alpha)

    def remember(self, state, action, reward, next_state, done):
        self.replay_buffer.append((state, action, reward, next_state, done))

    def act(self, state):
        if np.random.uniform(0,1) < self.epsilon:
            action = torch.tensor([[np.random.randint(self.action_size)]], device=self.device, dtype=torch.long)
        else:
            with torch.no_grad():
                action = self.main_network(self.encode_state(state).to(self.device)).argmax()
        return action.item()

    def train(self, batch_size):
        minibatch = self.replay_buffer.sample(batch_size)
        predicted_Q_values, target_Q_values = [], []
        for state, action, reward, new_state, done in minibatch:
            state = self.encode_state(state)
            new_state = self.encode_state(new_state)
            reward = torch.tensor([reward], device=self.device)

            if not done:
                with torch.no_grad():
                    target = reward + self.gamma * self.target_network(new_state).max()
            else:
                target = reward
            target_Q = self.main_network(state)
            target_Q[action] = target

            predicted_Q = self.main_network(state)

            predicted_Q_values.append(predicted_Q)
            target_Q_values.append(target_Q)

        loss = self.loss_fn(torch.stack(predicted_Q_values), torch.stack(target_Q_values))

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()
        return loss

    def encode_state(self, state):
        # one_hot_tensor = torch.tensor(self.maze.maze.flatten(), dtype=torch.float32, device=self.device)
        one_hot_tensor = torch.zeros(self.state_size, dtype=torch.float32, device=self.device)
        one_hot_tensor[state] = 1
        target_index = self.maze.destination[0] * self.maze.maze_size + self.maze.destination[1]
        one_hot_tensor[target_index] = 2
        return one_hot_tensor

    def update_target_network(self):
        self.target_network.load_state_dict(self.main_network.state_dict())


class DoubleDQNModel:
    def __init__(self, state_size, action_size, maze, device):
        param_dir = 'Simulation/Utils/'
        with open(param_dir + 'config.json', 'r') as file:
            self.params = json.load(file)

        self.state_size = state_size
        self.action_size = action_size
        self.device = device
        self.maze = maze
        self.buffer_size = self.params['BUFFER_SIZE']
        self.replay_buffer = ReplayBuffer(self.buffer_size)
        self.gamma = self.params['GAMMA']
        self.alpha = self.params['ALPHA']
        self.epsilon = self.params['EPSILON']
        self.epsilon_min = self.params['EPSILON_MIN']
        self.epsilon_decay = self.params['EPSILON_DECAY']
        self.update_rate = self.params['UPDATE_RATE']

        self.main_network = DQN(self.state_size, self.action_size).to(device=device)
        self.target_network = DQN(self.state_size, self.action_size).to(device=device)
        self.target_network.load_state_dict(self.main_network.state_dict())
        self.loss_fn = nn.MSELoss()
        self.optimizer = torch.optim.Adam(self.main_network.parameters(), lr=self.alpha)

    def remember(self, state, action, reward, next_state, done):
        self.replay_buffer.append((state, action, reward, next_state, done))

    def act(self, state):
        if np.random.rand() < self.epsilon:
            action = torch.tensor([[np.random.randint(self.action_size)]], device=self.device, dtype=torch.long)
        else:
            with torch.no_grad():
                action = self.main_network(self.encode_state(state).to(self.device)).argmax()
        return action.item()

    def train(self, batch_size):
        minibatch = self.replay_buffer.sample(batch_size)
        predicted_Q_values, target_Q_values = [], []
        for state, action, reward, next_state, done in minibatch:
            state = self.encode_state(state)
            next_state = self.encode_state(next_state)
            reward = torch.tensor([reward], device=self.device)

            predicted_Q = self.main_network(state)
            target_Q = predicted_Q.clone()
            if not done:
                with torch.no_grad():
                    next_action = self.main_network(next_state).argmax()
                target_value = reward + self.gamma * self.target_network(next_state)[next_action]
            else:
                target_value = reward
            target_Q[action] = target_value

            predicted_Q_values.append(predicted_Q)
            target_Q_values.append(target_Q)

        loss = self.loss_fn(torch.stack(predicted_Q_values), torch.stack(target_Q_values))

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        return loss

    def encode_state(self, state):
        one_hot_tensor = torch.zeros(self.state_size, dtype=torch.float32, device=self.device)
        one_hot_tensor[state] = 1
        target_index = self.maze.destination[0] * self.maze.maze_size + self.maze.destination[1]
        one_hot_tensor[target_index] = 2
        return one_hot_tensor

    def update_target_network(self):
        self.target_network.load_state_dict(self.main_network.state_dict())


class DuelDQN(nn.Module):
    def __init__(self, state_size, action_size):
        super(DuelDQN, self).__init__()
        self.layer1 = nn.Linear(state_size, 32)
        self.layer2 = nn.Linear(32, 16)

        self.value_layer1 = nn.Linear(16, 16)
        self.value = nn.Linear(16, 1)

        self.advantage_layer1 = nn.Linear(16, 16)
        self.advantage = nn.Linear(16, action_size)

    def forward(self, x):
        x = F.relu(self.layer1(x))
        x = F.relu(self.layer2(x))

        value = F.relu(self.value_layer1(x))
        value = self.value(value)

        advantage = F.relu(self.advantage_layer1(x))
        advantage = self.advantage(advantage)

        q_values = value + (advantage - advantage.mean())

        return q_values


class DuelingDQNModel:
    def __init__(self, state_size, action_size, maze, device):
        param_dir = 'Simulation/Utils/'
        with open(param_dir + 'config.json', 'r') as file:
            self.params = json.load(file)

        self.state_size = state_size
        self.action_size = action_size
        self.device = device
        self.maze = maze
        self.buffer_size = self.params['BUFFER_SIZE']
        self.replay_buffer = ReplayBuffer(self.buffer_size)
        self.gamma = self.params['GAMMA']
        self.alpha = self.params['ALPHA']
        self.epsilon = self.params['EPSILON']
        self.epsilon_min = self.params['EPSILON_MIN']
        self.epsilon_decay = self.params['EPSILON_DECAY']
        self.update_rate = self.params['UPDATE_RATE']

        self.main_network = DuelDQN(self.state_size, self.action_size).to(device=device)
        self.target_network = DuelDQN(self.state_size, self.action_size).to(device=device)
        self.target_network.load_state_dict(self.main_network.state_dict())
        self.loss_fn = nn.MSELoss()
        self.optimizer = torch.optim.Adam(self.main_network.parameters(), lr=self.alpha)

    def remember(self, state, action, reward, next_state, done):
        self.replay_buffer.append((state, action, reward, next_state, done))

    def act(self, state):
        if np.random.rand() < self.epsilon:
            action = torch.tensor([[np.random.randint(self.action_size)]], device=self.device, dtype=torch.long)
        else:
            with torch.no_grad():
                action = self.main_network(self.encode_state(state).to(self.device)).argmax()
        return action.item()

    def train(self, batch_size):
        minibatch = self.replay_buffer.sample(batch_size)
        predicted_Q_values, target_Q_values = [], []
        for state, action, reward, new_state, done in minibatch:
            state = self.encode_state(state)
            new_state = self.encode_state(new_state)
            reward = torch.tensor([reward], device=self.device)

            predicted_Q = self.main_network(state)
            target_Q = self.target_network(state)

            if not done:
                with torch.no_grad():
                    target = reward + self.gamma * self.target_network(new_state).max()
            else:
                target = reward
            target_Q[action] = target

            predicted_Q_values.append(predicted_Q)
            target_Q_values.append(target_Q)

        loss = self.loss_fn(torch.stack(predicted_Q_values), torch.stack(target_Q_values))

        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

        return loss

    def encode_state(self, state):
        one_hot_tensor = torch.zeros(self.state_size, dtype=torch.float32, device=self.device)
        one_hot_tensor[state] = 1
        target_index = self.maze.destination[0] * self.maze.maze_size + self.maze.destination[1]
        one_hot_tensor[target_index] = 2
        return one_hot_tensor

    def update_target_network(self):
        self.target_network.load_state_dict(self.main_network.state_dict())
