#include "pch.h"
#include <chrono>
#include "HamiltonianPath.h"
#include "ConsoleView.h"

// Disabled: Development testing: bench mark for algorithm
// Time per game(ms):    1145 Average Move each game:    12755
TEST(HamiltonianPath, MovePathMany)
{
	unsigned long moveCounter = 0;
	unsigned long averageMovements = 0;
	unsigned short counter = 0;
	unsigned short times = 300;
	HamiltonianPath moveMaker = HamiltonianPath();
	
    bool finsihedAll = true;
    auto start = std::chrono::high_resolution_clock::now();
    for (counter = 0; counter < times; counter++)
	{
		GameState testNormal = GameState(16, 16);
		moveCounter = 0;
		do
		{
			testNormal.MakeMove(moveMaker.MakeMove(testNormal));
			moveCounter++;
		} while (testNormal.IsLegalGame() && !testNormal.IsGameWon());

		if (!testNormal.IsGameWon())
		{
			finsihedAll = false;
			break;
		}
		else
		{
			averageMovements += moveCounter / times;
		}
	}
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    long long timePerGame = (duration.count() / times) / 1000;
    std::cout << "Time per game(ms):    " << timePerGame << " Average Move each game:    " << averageMovements << "\n";

	EXPECT_TRUE(finsihedAll);
}
