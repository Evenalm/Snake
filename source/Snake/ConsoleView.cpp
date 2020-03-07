#include <iostream>
#include <string>
#include "ConsoleView.h"
#include <vector>

void ConsoleView::Reset() { }

void ConsoleView::displayState(GameState& state)
{
	if (state.IsLegalGame())
	{
		std::vector<std::vector<int>>    board(state.GetBoardWidth(), std::vector<int>(state.GetBoardHeight()));
		for (unsigned int bodyPos = 0; bodyPos < state.GetSnakeSize(); bodyPos++)
		{
			board[state.GetSnakeBody(bodyPos).X][state.GetSnakeBody(bodyPos).Y] = -(int)(bodyPos + 1);
		}

		if (!ArePointsEqual(state.GetFruit(), InvalidGamePoint))
		{
			board[state.GetFruit().X][state.GetFruit().Y] = (int)GameState::CellType::Fruit;
		}

		for (int coloum = (state.GetBoardHeight() - 1); coloum >= 0; --coloum)
		{
			std::string rowRep;
			for (unsigned int row = 0; row < state.GetBoardWidth(); ++row)
			{
				if (board[row][coloum] < 0)
				{
					rowRep.append(std::to_string(-board[row][coloum]) + "\t");
				}
				else if (board[row][coloum] == (int)GameState::CellType::Fruit)
				{
					rowRep.append("F\t");
				}
				else
				{
					rowRep.append("[]\t");
				}
			}
			rowRep.append("\n");
			std::cout << rowRep;
		}
		std::cout << "////////////////////////////////////// \n";
	}
}

void ConsoleView::displayMessage(std::string& s)
{
   std::cout << s << "\n";
}

void ConsoleView::displayWinningMessage(GameState& state)
{
   std::cout << "You Won!" << "\n";
}

void ConsoleView::displayLosingMessage(GameState& state)
{
   std::cout << "You lost, your score: " << state.GetScore() << "\n";
}
