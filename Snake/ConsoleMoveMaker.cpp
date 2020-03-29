#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include <stdio.h>
#include "ConsoleMoveMaker.h"
#include "GameState.h"
#include "KeyPress.h"

ConsoleMoveMaker::ConsoleMoveMaker() : moveMade(GameState::Move::Up) { }

GameState::Move ConsoleMoveMaker::MakeMove(GameState& state)
{
    static int numInput = 300;

    /* clear buffer */
    std::cin.clear();
    fflush(stdin);

    /* Wait for Input or timeout */
    clock_t timer = 0;
    clock_t stopTimer = clock() + numInput;
    while (!_kbhit())
    {
        timer = clock();
        if (stopTimer < timer)
        {
            break;
        }
    }

    /* Sleep rest if early press */
    clock_t duration = timer - stopTimer;
    if (duration > 20)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }

    /* Get key press if there is one */
    if (_kbhit())
    {
        int c, ex;
        c = _getch();
        if (c == 224)
        {
            switch (ex = _getch())
            {
            case (int)KeyPress::Up:     /* H */
                moveMade = GameState::Move::Up;
                break;

            case (int)KeyPress::Down:   /* K */
                moveMade = GameState::Move::Down;
                break;

            case (int)KeyPress::Left:   /* M */
                moveMade = GameState::Move::Left;
                break;

            case (int)KeyPress::Right:  /* P */
                moveMade = GameState::Move::Right;
                break;
            }
        } // No deafault, keep last key press
    }

	return moveMade;
}

void ConsoleMoveMaker::Reset()
{
    moveMade = GameState::Move::Up;
}
