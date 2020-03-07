#include "HamiltonianPath.h"

HamiltonianPath::HamiltonianPath() : goForFruit(true), earlyLoop(false), goForFruitOnReturnPath(false) { }

GameState::Move HamiltonianPath::MakeMove(GameState& state)
{
	GameState::Move result = GameState::Move::Up;
	Point head = state.GetHead();
	Point tail = state.GetTail();
	Point fruit = state.GetFruit();


    /* Check reset conditions */
	if (state.WasFruitFoundLastTurn()) {   goForFruit = false; }
    if (head.X > fruit.Y)   {   goForFruitOnReturnPath = false; }
    if (head.Y == 0)    {   earlyLoop = false;  }


    /* Check start conditions */
    if (head.X < fruit.X)
    {
        if (head.Y == 0)
        {
            if (fruit.X < tail.X && tail.X - fruit.X >= 2)
            {
                goForFruit = true;
            }
        }
        else if (fruit.Y != 0)
        {
            if (tail.X < head.X && (fruit.X - head.X >= 2))
            {
                goForFruit = true;
            }
            else if (fruit.X - head.X >= 2 && fruit.X < tail.X && (tail.X - fruit.X >= 2))
            {
                goForFruit = true;
            }
        }
        else if ((tail.Y != 0) && (tail.X < head.X))
        {
            goForFruitOnReturnPath = true;
        }
    }

    if (head.Y != 0 && (fruit.X < head.X && tail.X < head.X))
    {
        earlyLoop = true;
    }


    /* Execute states */
	if (goForFruit)
	{
        unsigned int score = USHRT_MAX;
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			Point point = GetNextPoint(head, (GameState::Move)moveNmbr);
			unsigned int tempScore = GetManhattenDistance(point, fruit);

			if ((tempScore < score) && (point.X != fruit.X || 0 == tempScore) && !ArePointsEqual(point, state.GetSnakeBody(1)))
			{
				score = tempScore;
				result = (GameState::Move)moveNmbr;
			}
		}
	}
    else if (goForFruitOnReturnPath)
    {
        result = GameState::Move::Right;
    }
    else if (earlyLoop)
	{
		if (state.GetSnakeBody(1).Y < head.Y)
		{
			result = GameState::Move::Right;
		}
		else
		{
			result = GameState::Move::Down;
		}
	}
    else    /* Follow the Hamiltonian path */
    {
        if (head.Y == 0) 
        {
            if (head.X == 0)
            {
                result = GameState::Move::Up;
            }
            else
            {
                result = GameState::Move::Left;
            }
        }
        else if (head.X & 1) /* Check for odd even column */
        {
            if ((head.X == (state.GetBoardWidth() - 1)) || (head.Y != 1))
            {
                result = GameState::Move::Down;
            }
            else
            {
                result = GameState::Move::Right;
            }
        }
        else
        {
            if (head.Y == (state.GetBoardHeight() - 1))
            {
                result = GameState::Move::Right;
            }
            else
            {
                result = GameState::Move::Up;
            }
        }
    }

	return result;
}

void HamiltonianPath::Reset()
{
    goForFruit = true;
    earlyLoop = false;
    goForFruitOnReturnPath = false;
}
