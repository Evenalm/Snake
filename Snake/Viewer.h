#ifndef VIEWER_H
#define VIEWER_H

#include <string>
#include "GameState.h"

class Viewer
{
   public:
      virtual void Reset() = 0;
      virtual void displayState(GameState& state) = 0;
      virtual void displayMessage(std::string& s) = 0;
      virtual void displayWinningMessage(GameState& state) = 0;
      virtual void displayLosingMessage(GameState& state) = 0;
};

#endif // VIEWER_H