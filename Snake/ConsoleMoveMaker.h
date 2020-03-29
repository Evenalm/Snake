#ifndef CONSOLE_MOVE_MAKER_H
#define CONSOLE_MOVE_MAKER_H

#include "MoveMaker.h"

class ConsoleMoveMaker : public MoveMaker
{
    public:
        ConsoleMoveMaker();
        virtual GameState::Move MakeMove(GameState& state) override;
        virtual void Reset() override;

    private:
        GameState::Move moveMade;
};

#endif // CONSOLE_MOVE_MAKER_H

