#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <conio.h>
#include <stdio.h>
#include "ConsoleMinimalist.h"
#include "KeyPress.h"

ConsoleMinimalist::ConsoleMinimalist() : moveMade(GameState::Move::Up) { }

GameState::Move ConsoleMinimalist::MakeMove(GameState& state)
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
             /* Change for left right to actual snake movement */
            ex = _getch();
            if (ex == (int)KeyPress::Left)
            {
                moveMade = GetMinimalistMove(state.GetOrientation(), GameState::Move::Left);

            }
            else if (ex == (int)KeyPress::Right)
            {
                moveMade = GetMinimalistMove(state.GetOrientation(), GameState::Move::Right);
            }
        }
    }

    return moveMade;
}

void ConsoleMinimalist::Reset()
{
    moveMade = GameState::Move::Up;
}
