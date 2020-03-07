#ifndef ConsoleMinimalist_H
#define ConsoleMinimalist_H

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

#endif // ConsoleMinimalist_H