#ifndef HamiltonianPath_H
#define HamiltonianPath_H

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

#endif // HamiltonianPath_H