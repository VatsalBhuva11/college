import json
import pygame
import heapq
import numpy as np


def collect_waypoints(path):
    waypoints = []
    waypoint_interval = max(1, len(path) // 7)  # Collect 7 waypoints, or fewer if the path is short
    for i in range(waypoint_interval, len(path) - 1, waypoint_interval):
        waypoints.append(path[i])
    return waypoints


def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


class MazeEnv:
    def __init__(self):
        param_dir = 'Simulation/Utils/'
        with open(param_dir + 'config.json', 'r') as file:
            self.params = json.load(file)
        self.data_dir = self.params['DATA_DIR'] + self.params['MAZE_DIR']

        self.maze_size = self.params['SIZE']
        self.cell_size = self.params['CELL_SIZE']
        self.maze = None
        self.is_guided_maze = True if self.params['GUIDED_MAZE'] else False
        self.directions = np.array([[1, 0], [-1, 0], [0, 1], [0, -1]])  # [0 -> D, 1 -> U, 2 -> R, 3 -> L]
        self.window_size = (self.cell_size * self.maze_size, self.cell_size * self.maze_size)

        self.screen = None
        self.clock = None
        self.path = None
        self.fps = self.params['FPS']
        self.WHITE = (255, 255, 255)

        self.source = None
        self.destination = None
        self.waypoints = [] if self.is_guided_maze else None

    def env_setup(self):
        pygame.init()
        self.screen = pygame.display.set_mode(self.window_size)
        pygame.display.set_caption('Maze Simulation')
        self.clock = pygame.time.Clock()

    def distance_to_goal(self, agent_position):
        dist = np.linalg.norm(agent_position - self.destination)
        return dist

    def update_display(self, agent):
        self.screen.fill(self.WHITE)
        for y in range(self.maze_size):
            for x in range(self.maze_size):
                color = (0, 0, 0) if self.maze[y, x] == 1 else (255, 255, 255)
                pygame.draw.rect(self.screen, color,
                                 pygame.Rect(x * self.cell_size, y * self.cell_size,
                                             self.cell_size, self.cell_size))

        if self.path:
            for i in range(len(self.path) - 1):
                start_pos = (self.path[i][1] * self.cell_size + self.cell_size // 2,
                             self.path[i][0] * self.cell_size + self.cell_size // 2)
                end_pos = (self.path[i + 1][1] * self.cell_size + self.cell_size // 2,
                           self.path[i + 1][0] * self.cell_size + self.cell_size // 2)
                pygame.draw.line(self.screen, (0, 0, 255), start_pos, end_pos, 3)

        pygame.draw.circle(self.screen, (0, 255, 0),
                           (self.source[1] * self.cell_size + self.cell_size // 2,
                            self.source[0] * self.cell_size + self.cell_size // 2), 8)

        pygame.draw.circle(self.screen, (255, 0, 255),
                           (self.destination[1] * self.cell_size + self.cell_size // 2,
                            self.destination[0] * self.cell_size + self.cell_size // 2), 8)

        pygame.draw.circle(self.screen, (139, 69, 19),
                           (agent.position[1] * self.cell_size + self.cell_size // 2,
                            agent.position[0] * self.cell_size + self.cell_size // 2), agent.radius)

        if self.is_guided_maze:
            for waypoint in self.waypoints:
                pygame.draw.circle(self.screen, (255, 165, 0),
                                   (waypoint[1] * self.cell_size + self.cell_size // 2,
                                    waypoint[0] * self.cell_size + self.cell_size // 2), 6)

        pygame.display.update()
        self.clock.tick(self.fps)

    def find_path(self):
        self.a_star()

    def load_src_dst(self):
        filename = self.params['LOCATION_FILENAME']
        location = np.load(self.data_dir + filename)
        self.source, self.destination = location[0], location[1]

    def generate_maze(self, p):
        # - 2 because the boundaries are walls by default
        n = int((self.maze_size - 2) ** 2 * p)
        self.maze = np.ones((self.maze_size, self.maze_size), dtype=int)

        walls = []
        
        # start point for generating maze (0-based)
        start_x, start_y = np.random.choice(range(1, self.maze_size - 1)), 1
        self.maze[start_x, start_y] = 0


        for direction in self.directions:
            nx, ny = start_x + direction[0], start_y + direction[1]
            if 1 < nx < self.maze_size - 1 and 1 < ny < self.maze_size - 1:
                walls.append((nx, ny, start_x, start_y))

        while walls:
            idx_no = len(walls)
            wall = walls[np.random.choice(idx_no)]
            x, y, px, py = wall
            if self.maze[x, y] == 1:
                adjacent_passages = sum(
                    self.maze_size - 1 > x + direction[0] >= 1 and
                    self.maze_size - 1 > y + direction[1] >= 1 and
                    self.maze[x + direction[0], y + direction[1]] == 0 for direction in self.directions
                )

                if adjacent_passages == 1:
                    self.maze[x, y] = 0
                    for direction in self.directions:
                        nx, ny = x + direction[0], y + direction[1]
                        if self.maze_size - 1 > nx > 0 and self.maze_size - 1 > ny > 0 and self.maze[nx, ny] == 1:
                            walls.append((nx, ny, x, y))
            walls.remove(wall)
        internal_cells = [(i, j) for i in range(1, self.maze_size - 1) for j in range(1, self.maze_size - 1)]
        np.random.shuffle(internal_cells)

        internal_wall_count = np.sum(self.maze[1:-1, 1:-1] == 1)
        # if less walls, then choose random empty spots and convert to walls
        while internal_wall_count < n:
            x, y = internal_cells.pop()
            if self.maze[x, y] == 0:  
                self.maze[x, y] = 1
                internal_wall_count += 1
        # if more walls, then choose random walls and convert to empty spaces
        while internal_wall_count > n:
            x, y = internal_cells.pop()
            if self.maze[x, y] == 1: 
                self.maze[x, y] = 0
                internal_wall_count -= 1

    def generate_src_dst(self):
        
        # source will always be on row-(1) (0-based) since 0th is boundary
        self.source = np.array((1, np.random.choice(range(1, self.maze_size))))
        # destination will always be on row-(n-2) (0-based) since n-1th is boundary
        self.destination = np.array((self.maze_size - 2, np.random.choice(range(1, self.maze_size))))

        while not self.is_valid_position(self.source):
            self.source = np.array((1, np.random.choice(range(1, self.maze_size))))
        while not self.is_valid_position(self.destination):
            self.destination = np.array((self.maze_size - 2, np.random.choice(range(1, self.maze_size))))

        filename = self.params['LOCATION_FILENAME']
        if self.source is not None and self.destination is not None:
            location = np.vstack((self.source, self.destination))
            np.save(self.data_dir + filename, location)

    def is_valid_position(self, position):
        x, y = position
        return 0 <= x < self.maze_size and 0 <= y < self.maze_size and self.maze[x, y] == 0

    def a_star(self):
        start, goal = self.source, self.destination
        if isinstance(start, np.ndarray):
            start = tuple(start)
        if isinstance(goal, np.ndarray):
            goal = tuple(goal)

        open_set = []
        heapq.heappush(open_set, (0 + heuristic(start, goal), 0, start))
        came_from = {}
        g_score = {start: 0}
        f_score = {start: heuristic(start, goal)}

        while open_set:
            _, current_g, current = heapq.heappop(open_set)
            if current == goal:
                self.path = []
                while current in came_from:
                    self.path.append(current)
                    current = came_from[current]
                self.path.append(start)
                self.path.reverse()

                # If guided maze, collect waypoints
                if self.is_guided_maze:
                    self.waypoints = collect_waypoints(self.path) if self.is_guided_maze else None

                return self.path

            for direction in self.directions:
                neighbor = (current[0] + direction[0], current[1] + direction[1])
                if self.is_valid_position(neighbor):
                    tentative_g_score = g_score[current] + 1
                    if neighbor not in g_score or tentative_g_score < g_score[neighbor]:
                        came_from[neighbor] = current
                        g_score[neighbor] = tentative_g_score
                        f_score[neighbor] = tentative_g_score + heuristic(neighbor, goal)
                        if neighbor not in [i[2] for i in open_set]:
                            heapq.heappush(open_set, (f_score[neighbor], tentative_g_score, neighbor))


def main():
    # Initialize the Maze Environment
    env = MazeEnv()
    
    # Load or Generate the Maze and Source/Destination
    env.env_setup()
    env.generate_maze(p=0.3)  # Adjust `p` to control the density of walls
    env.generate_src_dst()
    env.find_path()

    # Dummy agent data
    class Agent:
        def __init__(self, position, radius=8):
            self.position = position
            self.radius = radius
    
    agent = Agent(position=env.source)

    # Run the simulation loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        # Update the agent position here if needed

        # Update the display
        env.update_display(agent)

    pygame.quit()


if __name__ == "__main__":
    main()
