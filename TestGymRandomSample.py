# Environment page:
# https://gym.openai.com/envs/CartPole-v0

import gym
import gym_snake
from SnakePort import GameState

env = gym.make('snake-v0')
env.reset()

box = env.observation_space
env.action_space
action = env.action_space.sample()

done = False
while not done:
	env.render()
	observation, reward, done, _ = env.step(env.action_space.sample())
	sec = input("Wait for input")



