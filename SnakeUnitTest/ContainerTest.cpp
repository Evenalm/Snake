#include "pch.h"
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include "Point.h"
#include "GameState.h"


/* Last Results:
Time taken by Vector: 12572745 microseconds
Time taken by Deque:  865851 microseconds
*/
TEST(GameContainer, VectorVsDeque)
{
	unsigned int GameSizeVec = 256 * 16;
	unsigned int movesPrApple = 16000;
	Point point = { 0,0 };

    std::vector<Point> testVector;
    testVector.reserve(GameSizeVec);
	testVector.push_back({ 0,2 });
	testVector.push_back({ 0,1 });
	testVector.push_back({ 0,0 });
	auto start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSizeVec; bodySize++)
	{
		testVector.insert(testVector.begin(), point);
		for (unsigned int moves = 0; moves < movesPrApple; moves++)
		{
			testVector.insert(testVector.begin(), point);
			testVector.pop_back();
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationVector = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by Vector: " << durationVector.count() << " microseconds" << "\n";

	unsigned int GameSizeDeq = 256 * 16;
    std::deque<Point> testDeque;
    testDeque.push_back({ 0, 2 });
	testDeque.push_back({ 0, 1 });
	testDeque.push_back({ 0, 0 });
	start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSizeDeq; bodySize++)
	{
		testDeque.insert(testDeque.begin(), point);
		for (unsigned int moves = 0; moves < movesPrApple; moves++)
		{
			testDeque.insert(testDeque.begin(), point);
			testDeque.pop_back();
		}
	}
	stop = std::chrono::high_resolution_clock::now();

	auto durationDeque = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by Deque:  " << durationDeque.count() << " microseconds" << "\n";

	EXPECT_EQ(testVector.size(), GameSizeVec);
	EXPECT_EQ(testDeque.size(), GameSizeDeq);
	EXPECT_GT(durationVector, durationDeque);
}

class TestTable
{ 
public:
    int move;
    TestTable* parentTable;
	unsigned short x_pos;
    unsigned short y_pos;
	int costSoFar;
	int costHeuristic;
	bool hitFriut;

	TestTable() : hitFriut(0), costHeuristic(0), costSoFar(0), x_pos(0), y_pos(0), parentTable(NULL), move(0) { };
};

/* Last Results:
Time taken by Vector: 3511399 microseconds
Time taken by List:   6654885 microseconds
*/
TEST(AstarContainer, VectorVsList)
{
	unsigned int GameSize = 256 * 256;
	TestTable point = TestTable();

	std::vector<TestTable> testVector;
	testVector.reserve(GameSize);
	testVector.push_back(point);
	auto start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSize; bodySize++)
	{
		unsigned int entry = rand() % (bodySize);
		TestTable newPoint = testVector[entry];

		testVector.push_back(point);
		testVector.push_back(point);
		testVector.push_back(point);
		testVector.erase(testVector.begin() + entry);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationVector = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by Vector: " << durationVector.count() << " microseconds" << "\n";

	std::list<TestTable> testList;
	std::list<TestTable>::iterator it1;
	testList.push_back(point);
	start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSize; bodySize++)
	{
		unsigned int entry = rand() % (bodySize);
		it1 = testList.begin();
		advance(it1, entry);
		TestTable newPoint = *it1;

		testList.push_back(point);
		testList.push_back(point);
		testList.push_back(point);
		testList.erase(it1);
	}
	stop = std::chrono::high_resolution_clock::now();

	auto durationList = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by List:   " << durationList.count() << " microseconds" << "\n";

	EXPECT_GT(durationList, durationVector);
}

/* Last Results:
Time taken by Vector: 548462 microseconds
Time taken by List:   5663988 microseconds
*/
TEST(AstarContainer, VectorVsList_Pointers)
{
	unsigned int GameSize = 256 * 256;

	std::vector<TestTable*> testVector;
	std::vector<TestTable*> testVectorClosed;
	testVector.reserve(GameSize);
	testVector.push_back(new TestTable());
	auto start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSize; bodySize++)
	{
		unsigned int entry = rand() % (bodySize);
		TestTable* newPoint = testVector[entry];
		testVectorClosed.push_back(newPoint);

		testVector.push_back(new TestTable());
		testVector.push_back(new TestTable());
		testVector.push_back(new TestTable());
		testVector.erase(testVector.begin() + entry);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationVector = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by Vector: " << durationVector.count() << " microseconds" << "\n";

	std::list<TestTable*> testList;
	std::list<TestTable*> testListClosed;
	std::list<TestTable*>::iterator it1;
	testList.push_back(new TestTable());
	start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSize; bodySize++)
	{
		unsigned int entry = rand() % (bodySize);
		it1 = testList.begin();
		advance(it1, entry);
		TestTable* newPoint = *it1;
		testListClosed.push_back(newPoint);

		testList.push_back(new TestTable());
		testList.push_back(new TestTable());
		testList.push_back(new TestTable());
		testList.erase(it1);
	}

	//Deallocate all memory
	it1 = testList.begin();
	for (unsigned int i = 0; i < testList.size(); ++i) 
	{
		it1++;
		delete *it1;
	}
	testList.clear();

	//Deallocate all memory
	it1 = testListClosed.begin();
	for (unsigned int i = 0; i < testListClosed.size(); ++i) 
	{
		it1++;
		delete* it1;
	}
	testListClosed.clear();

	stop = std::chrono::high_resolution_clock::now();

	auto durationList = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by List:   " << durationList.count() << " microseconds" << "\n";

	EXPECT_GT(durationList, durationVector);
}

/* Last Results:
Time taken by VectorP: 543998 microseconds
Time taken by Vector:  3367311 microseconds
*/
TEST(AstarVector, PointerVsCopy)
{
	unsigned int GameSize = 256 * 256;
	TestTable point = TestTable();

	std::vector<TestTable*> testVectorP;
	std::vector<TestTable*> testVectorClosed;
	testVectorP.reserve(GameSize);
	testVectorP.push_back(new TestTable());
	auto start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSize; bodySize++)
	{
		unsigned int entry = rand() % (bodySize);
		TestTable* newPoint = testVectorP[entry];
		testVectorClosed.push_back(newPoint);

		testVectorP.push_back(new TestTable());
		testVectorP.push_back(new TestTable());
		testVectorP.push_back(new TestTable());
		testVectorP.erase(testVectorP.begin() + entry);
	}
	auto stop = std::chrono::high_resolution_clock::now();

	auto durationVectorP = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by VectorP: " << durationVectorP.count() << " microseconds" << "\n";

	std::vector<TestTable> testVector;
	testVector.reserve(GameSize);
	testVector.push_back(point);
	start = std::chrono::high_resolution_clock::now();
	for (unsigned int bodySize = 3; bodySize < GameSize; bodySize++)
	{
		unsigned int entry = rand() % (bodySize);
		TestTable newPoint = testVector[entry];

		testVector.push_back(point);
		testVector.push_back(point);
		testVector.push_back(point);
		testVector.erase(testVector.begin() + entry);
	}
	stop = std::chrono::high_resolution_clock::now();

	auto durationVector = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Time taken by Vector:  " << durationVector.count() << " microseconds" << "\n";

	EXPECT_GT(durationVector, durationVectorP);
}
