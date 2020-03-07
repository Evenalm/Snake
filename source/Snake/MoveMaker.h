#ifndef MoveMaker_H
#define MoveMaker_H

#include "GameState.h"

class MoveMaker
{
   public:
      virtual GameState::Move MakeMove(GameState& state) = 0;
      virtual void Reset() = 0;
};

#endif // MoveMaker_H

