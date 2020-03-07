#include "GameState.h"

GameState::GameState(unsigned short widht, unsigned short height)
{
	if (( widht >= 3) && widht < USHRT_MAX && (height >= 3) && height < USHRT_MAX)
	{
		SetDeafultConfig(widht, height);
	}
	else
	{
		SetDeafultConfig(3, 3);
	}
}

GameState::GameState(std::deque<Point> currentPositions, Point goal, unsigned short boardSize)
{
	SetDeafultConfig(boardSize, boardSize);
   this->currentPositions = currentPositions;
   this->fruitPosition = goal;
   this->width_X = boardSize;
   this->height_Y = boardSize;
}

void GameState::Reset()
{
	this->SetDeafultConfig(width_X, height_Y);
}

void GameState::SetDeafultConfig(unsigned short width, unsigned short hight)
{
	currentPositions.clear();
	currentPositions.push_back({ 0, 2 });
	currentPositions.push_back({ 0, 1 });
	currentPositions.push_back({ 0, 0 });

    width_X = width;
    height_Y = hight;
	board.reserve((unsigned int)width * hight);
    for (unsigned short ix = 0; ix < width_X; ix++)
    {
        for (unsigned short iy = 0; iy < height_Y; iy++)
        {
            board.push_back({ ix, iy });
        }
    }

	fruitPosition = { width / 2u, hight / 2u };
}

void GameState::MakeMove(Move nextMove)
{
	currentPositions.insert(currentPositions.begin(), GetNextPoint(currentPositions[0], nextMove));
	WasFruitFound = ArePointsEqual(currentPositions[0], fruitPosition);
	if (WasFruitFound)
	{
		fruitPosition = GetNewGoalPosition();
	}
	else
	{
		currentPositions.pop_back();
	}
}

unsigned int GameState::GetScore()
{
   return currentPositions.size();
}

bool GameState::IsLegalGame()
{
   bool foundCollision = false;
   for (unsigned int bodyNode = 1; bodyNode < currentPositions.size(); bodyNode++)
   {
	   if (ArePointsEqual(currentPositions[0], currentPositions[bodyNode]))
	   {
		   foundCollision = true;
		   break;
	   }
   }

   return !(currentPositions[0].X >= width_X || currentPositions[0].Y >= height_Y || foundCollision);
}

bool GameState::IsGameWon()
{
   return currentPositions.size() >= (width_X * height_Y);
}

bool GameState::WasFruitFoundLastTurn()
{
	return WasFruitFound;
}

unsigned int GameState::GetBoardSize()
{
	return width_X * height_Y;
}

unsigned short GameState::GetBoardWidth()
{
	return width_X;
}

unsigned short GameState::GetBoardHeight()
{
	return height_Y;
}

unsigned int GameState::GetSnakeSize()
{
	return currentPositions.size();
}

Point GameState::GetFruit()
{
	return fruitPosition;
}

Point GameState::GetHead()
{
	return currentPositions[0];
}

Point GameState::GetTail()
{
	return currentPositions[currentPositions.size() - 1];
}

Point GameState::GetSnakeBody(unsigned int position)
{
	return currentPositions[position];
}

GameState::CellType GameState::GetCellType(Point point)
{
	GameState::CellType returnValue = GameState::CellType::Open;
	if (ArePointsEqual(this->fruitPosition, point))
	{
		returnValue = GameState::CellType::Fruit;
	}
	else if (((point.X >= width_X || point.X < 0) || (point.Y >= height_Y || point.Y < 0)))
	{
		returnValue = GameState::CellType::Wall;
	}
	else
	{
		for (unsigned int bodyNode = 0; bodyNode < currentPositions.size(); bodyNode++)
		{
			if (ArePointsEqual(point, currentPositions[bodyNode]))
			{
				returnValue = GameState::CellType::Body;
				break;
			}
		}
	}

	return returnValue;
}

GameState::Orientation GameState::GetOrientation()
{
    GameState::Orientation resultOrientation;
    /* Check if vertical: north or south facing */
    if (currentPositions[0].X == currentPositions[1].X)
    {
        if (currentPositions[0].Y > currentPositions[1].Y)
        {
            resultOrientation =  GameState::Orientation::North;
        }
        else 
        {
            resultOrientation = GameState::Orientation::South;
        }
    }
    else // Horisontal: east or west
    {
        if (currentPositions[0].X > currentPositions[1].X)
        {
            resultOrientation = GameState::Orientation::East;
        }
        else
        {
            resultOrientation = GameState::Orientation::West;
        }
    }

    return resultOrientation;
}

Point GameState::GetNewGoalPosition()
{
    Point returnValue = InvalidGamePoint;
   if (!IsGameWon())
   {
       std::vector<Point> boardCopy = board;
	  for (unsigned int bodyNode = 0; bodyNode < currentPositions.size(); bodyNode++)
	  {
		  for (unsigned int fruitNode = 0; fruitNode < boardCopy.size(); fruitNode++)
		  {
			  if (ArePointsEqual(boardCopy[fruitNode], currentPositions[bodyNode]))
			  {
                  boardCopy.erase(boardCopy.begin() + fruitNode);
			  }
		  }
      }

      int index = (rand() % (int)boardCopy.size());
      returnValue = boardCopy[index];
   }

   return returnValue;
}

Point GetNextPoint(Point position, GameState::Move move)
{
    position.X += (GameState::Move::Right == move);
    position.X -= (GameState::Move::Left == move);
    position.Y -= (GameState::Move::Down == move);
    position.Y += (GameState::Move::Up == move);
    
	return position;
}

GameState::Move GetMinimalistMove(GameState::Orientation orientation, GameState::Move move)
{
    if (move == GameState::Move::Left)
    {
        if (orientation == GameState::Orientation::North)
        {
            move = GameState::Move::Left;
        }
        else if (orientation == GameState::Orientation::South)
        {
            move = GameState::Move::Right;
        }
        else if (orientation == GameState::Orientation::West)
        {
            move = GameState::Move::Down;
        }
        else
        {
            move = GameState::Move::Up;
        }
    }
    else if (move == GameState::Move::Right)
    {
        if (orientation == GameState::Orientation::North)
        {
            move = GameState::Move::Right;
        }
        else if (orientation == GameState::Orientation::South)
        {
            move = GameState::Move::Left;
        }
        else if (orientation == GameState::Orientation::West)
        {
            move = GameState::Move::Up;
        }
        else
        {
            move = GameState::Move::Down;
        }
    }

    return move;
}
