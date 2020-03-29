#ifndef MOVE_MAKER_H
#define MOVE_MAKER_H

#include "GameState.h"

class MoveMaker
{
   public:
      virtual GameState::Move MakeMove(GameState& state) = 0;
      virtual void Reset() = 0;
};

#endif // MOVE_MAKER_H

