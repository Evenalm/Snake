#ifndef HAMILTONIAN_PATH_H
#define HAMILTONIAN_PATH_H

#include "MoveMaker.h"

class HamiltonianPath :	public MoveMaker
{
	public:
		HamiltonianPath();
		GameState::Move MakeMove(GameState& state) override;
		virtual void Reset() override;

	private:
		bool goForFruit;
		bool earlyLoop;
		bool goForFruitOnReturnPath;
};

#endif // HAMILTONIAN_PATH_H