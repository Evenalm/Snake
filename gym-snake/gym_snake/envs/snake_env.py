import gym
import numpy as np
from gym import error, spaces, utils
from gym.utils import seeding
from SnakePort import GameState
from SnakePort import Point
from SnakePort import GetNextPoint
from SnakePort import InvalidGamePoint

class SnakeEnv(gym.Env):
	metadata = {'render.modes': ['human']}
	
	def __init__(self, game_size = 8):
		self.game = GameState(game_size, game_size)

		# Create a start state to copy to make new iterations faster
		self.start_state = []
		for i in range(game_size):
			self.start_state += [[]]
			for j in range(game_size):
				self.start_state[i] += [0]
		
		bodySize = self.game.GetSnakeSize()
		for bodyPos in range(bodySize):
			bodyPoint = self.game.GetSnakeBody(bodyPos)
			self.start_state[bodyPoint.X][bodyPoint.Y] = bodySize
			bodySize -= 1	
		
		fruit = self.game.GetFruit()
		if(InvalidGamePoint != fruit):
			self.start_state[fruit.X][fruit.Y] = -1

		self.state = self.start_state.copy()
		
		# Setup Gym
		self.action_space = spaces.Discrete(GameState.MoveAsInt(GameState.Move.Count))
		self.observation_space = spaces.Box(low=-1, high=self.game.GetBoardSize(), shape=(game_size, game_size), dtype=np.int)
		self.done = False
		self.reward_func = None
		self.rewards = [ -5.0, 1.0 / (game_size * game_size), -5.0, 0.5, 0.5, -5.0 ]
		self.reward_range = (min(self.rewards) * 2, max(self.rewards) * 2)
		self.reward = 0
		self.info = {}

	def set_rewards(self, rewards, min, max, func = None):
		self.rewards = rewards
		self.reward_func = func
		self.reward_range = (min, max)

	def step(self, move):
		cellType = self.game.GetCellType(GetNextPoint(self.game.GetHead(),GameState.Move(move)))
		self.reward = self.rewards[GameState.CellTypeAsInt(cellType)]
		oldTail = self.game.GetTail()
		self.game.MakeMove(GameState.Move(move))

		if(self.game.IsGameWon()):
			self.reward += self.rewards[4]
			self.done = True

		elif(not self.game.IsLegalGame()):
			self.reward += self.rewards[5]
			self.done = True
		
		self.update_state(oldTail)

		return [self.state, self.reward, self.done, self.info]

	def update_state(self, oldTail):
		if(self.done): 
			return
			
		bodySize = self.game.GetSnakeSize()
		for bodyPos in range(bodySize):
			bodyPoint = self.game.GetSnakeBody(bodyPos)
			self.state[bodyPoint.X][bodyPoint.Y] = bodySize
			bodySize -= 1			

		if(not self.game.WasFruitFoundLastTurn()):
			self.state[oldTail.X][oldTail.Y] = 0
			
		fruit = self.game.GetFruit()
		if(InvalidGamePoint != fruit):
			self.state[fruit.X][fruit.Y] = -1
	
	def reset(self):
		self.game.Reset()
		self.state = self.start_state.copy()
		self.done = False;
		return self.state

	def render(self, step):
		if(self.done): 
			return
			
		for i in range(self.game.GetBoardHeight() -1, -1, -1):
			string = ""
			for j in range(self.game.GetBoardWidth()):
				string += str(self.state[j][i]) + " " 
			print(string)

		print("")