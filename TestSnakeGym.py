import gym
import gym_snake
from SnakePort import GameState
from SnakePort import HamiltonianPath

env = gym.make('snake-v0')
env.reset()

box = env.observation_space
action = env.action_space

print(box)
print(action)

done = False
action = 0
actionSequence = [0, 2, 3, 1]
totalReward = 0
totalMoves = 0
env.reset()
while not done:
	#env.render()
	observation, reward, done, _ = env.step(actionSequence[action])
	totalMoves += 1
	totalReward += reward

	action += 1
	if(action > 3):
		action = 0

print("Result Infinite loop")
print(totalReward)
print(totalMoves)

hamiltonian = HamiltonianPath()
done = False
totalReward = 0
totalMoves = 0
env.reset()
while not done:
	#env.render()
	action = hamiltonian.MakeMove(env.game)
	observation, reward, done, _ = env.step(action)
	totalMoves += 1
	totalReward += reward

print("Hamiltonian implementation")
print("Total Moves")
print(totalMoves)
print("Total score:")
print(totalReward)

highestMoves = 0
randomSearchResults = []
for i in range(5000):
	done = False
	totalReward = 0
	totalMoves = 0
	env.reset()
	while not done:
		#env.render()
		observation, reward, done, _ = env.step(env.action_space.sample())
		totalMoves += 1
		totalReward += reward

	if(highestMoves < totalMoves):
		highestMoves = totalMoves
	randomSearchResults.append(totalMoves)

print("Average result from random moves")
print((sum(randomSearchResults) / len(randomSearchResults)))
print("Highest number of moves")
print(highestMoves)