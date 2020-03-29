#ifndef CONSOLE_MINIMALIST_H
#define CONSOLE_MINIMALIST_H

#include "MoveMaker.h"

class ConsoleMinimalist : public MoveMaker
{
    public:
        ConsoleMinimalist();
        virtual GameState::Move MakeMove(GameState& state) override;
        virtual void Reset() override;

    private:
        GameState::Move moveMade;
};

#endif // CONSOLE_MINIMALIST_H