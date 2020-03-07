#ifndef ConsoleMoveMaker_H
#define ConsoleMoveMaker_H

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

#endif // ConsoleMoveMaker_H

