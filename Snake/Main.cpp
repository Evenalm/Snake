#include <iostream>
#include <time.h>
#include "MoveMaker.h"
#include "HamiltonianPath.h"
#include "ConsoleMoveMaker.h"
#include "ConsoleMinimalist.h"
#include "ConsoleView.h"

int main(int argc, char** argv)
{
    srand((unsigned)time(NULL)); /* Get new random numbers each time */
    std::string goAgainMessage("Press Enter to go again! (Or E to Exit...)");
    std::string response("I would love to go again! ");

    MoveMaker* tempMM = NULL;
    if (argc >= 2)
    {
        std::string GameType(argv[1]);
        if (GameType.find("Play") != std::string::npos)
        {
            tempMM = new ConsoleMoveMaker();
        }
        else if (GameType.find("Minimalist") != std::string::npos)
        {
            tempMM = new ConsoleMinimalist();
        }
        else if (GameType.find("Hamiltonian") != std::string::npos)
        {
            tempMM = new HamiltonianPath();
        }
    }

    if (NULL == tempMM)
    {
        tempMM = new ConsoleMoveMaker();
    }

    std::unique_ptr<Viewer> output = std::unique_ptr<ConsoleView>(new ConsoleView());
    std::unique_ptr<MoveMaker> input = std::unique_ptr<MoveMaker>(std::move(tempMM));
    GameState game = GameState(16, 16);
    while (true)
    {
        do
        {
            output->displayState(game);
            game.MakeMove(input->MakeMove(game));

        } while (game.IsLegalGame() && !game.IsGameWon());

        output->displayState(game);
        if (game.IsGameWon())
        {
            output->displayWinningMessage(game);
        }
        else
        {
            output->displayLosingMessage(game);
        }
        output->displayMessage(goAgainMessage);
        getline(std::cin, response);

        if (response.find("E") == std::string::npos)
        {
            game.Reset();
            output->Reset();
            input->Reset();
        }
        else
        {
            break;
        }
    }

    output.release();
    input.release();
}
