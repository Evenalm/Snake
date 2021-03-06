#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <deque>
#include <vector>
#include "Point.h"

class GameState
{
	public:
		enum class Move { Up, Left, Right, Down, Count };
		enum class CellType { Wall, Open, Body, Fruit };
		enum class Orientation { North, South, East, West };
		static int MoveAsInt(Move move) { return (int)move; };
		static int CellTypeAsInt(CellType type) { return (int)type; };
		static int OrientationAsInt(Orientation ori) { return (int)ori; };

		GameState(unsigned short widht = 3, unsigned short height = 3);
		GameState(std::deque<Point> currentPositions, Point goal, unsigned short boardSize);

		void MakeMove(Move nextMove);
		
		void Reset();
		bool IsGameWon();
		bool IsLegalGame();
		bool WasFruitFoundLastTurn();
		unsigned int GetScore();
		unsigned int GetBoardSize();
        unsigned int GetSnakeSize();
        unsigned short GetBoardWidth();
		unsigned short GetBoardHeight();
		Point GetFruit();
		Point GetHead();
		Point GetTail();
		Point GetSnakeBody(unsigned int position);
        CellType GetCellType(Point point);
        Orientation GetOrientation();

    private:
        bool WasFruitFound = false;
        unsigned int width_X;
        unsigned int height_Y;       
        Point fruitPosition;
        std::deque<Point> currentPositions;
        std::vector<Point> board;

        Point GetNewGoalPosition();
        void SetDeafultConfig(unsigned short width, unsigned short hight);
};

const Point InvalidGamePoint = { USHRT_MAX, USHRT_MAX };

Point GetNextPoint(Point position, GameState::Move move);
GameState::Move GetMinimalistMove(GameState::Orientation orientation, GameState::Move move);

#endif // GAME_STATE_H