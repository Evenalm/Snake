#include "pch.h"
#include <chrono>
#include "Point.h"

/* Last Results:
Time(micro sec) Set each time:        389
Time(micro sec) Copy:                 92
*/
std::vector<Point> testvecCopy;
std::vector<Point> testVec;
TEST(Fastest, TestCopyVsAssign)
{
	unsigned short gameSize = 256;
	auto start = std::chrono::high_resolution_clock::now();
	testVec.reserve(gameSize * gameSize);
	for (unsigned short ix = 0; ix < gameSize; ix++)
	{
		for (unsigned short iy = 0; iy < gameSize; iy++)
		{
			testVec.push_back({ ix, iy });
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto durationSetEach = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	start = std::chrono::high_resolution_clock::now();
	testvecCopy = testVec;
	stop = std::chrono::high_resolution_clock::now();
	auto durationCopy = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time(micro sec) Set each time:    " << durationSetEach.count() << "\n";
	std::cout << "Time(micro sec) Copy:             " << durationCopy.count() << "\n";

	EXPECT_EQ(testVec.size(), testvecCopy.size());
}
