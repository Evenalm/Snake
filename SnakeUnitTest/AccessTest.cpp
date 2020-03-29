#include "pch.h"
#include <chrono>
#include "GameState.h"

class TestPointSetGet
{
public:
	TestPointSetGet() : X(0), Y(0) {}
	TestPointSetGet(unsigned short x, unsigned short y) : X(x), Y(y) {}
	unsigned short GetX() { return this->X; }
	unsigned short GetY() { return this->Y; }
	void SetX(unsigned short x) { this->X = x; }
	void SetY(unsigned short y) { this->Y = y; }

private:
	unsigned short X;
	unsigned short Y;
	friend bool operator==(TestPointSetGet const& item1, TestPointSetGet const& item2)
	{
		return (item1.X == item2.X) && (item1.Y == item2.Y);
	}
};

class TestPointPublic
{
public:
	TestPointPublic() : X(0), Y(0) {}
	TestPointPublic(unsigned short x, unsigned short y) : X(x), Y(y)  {}
	unsigned short X;
	unsigned short Y;

private:
	friend bool operator==(TestPointPublic const& item1, TestPointPublic const& item2)
	{
		return (item1.X == item2.X) && (item1.Y == item2.Y);
	}
};

struct TestStruct
{
	unsigned short X;
	unsigned short Y;
};
bool TestStruct_Equal(TestStruct const& item1, TestStruct const& item2) 
{ return (item1.X == item2.X) && (item1.Y == item2.Y); }

struct TestStructFunc
{
	unsigned short X;
	unsigned short Y;

private:
	friend bool operator==(TestStructFunc const& item1, TestStructFunc const& item2)
	{
		return (item1.X == item2.X) && (item1.Y == item2.Y);
	}
	friend bool operator!=(TestStructFunc const& item1, TestStructFunc const& item2)
	{
		return !(item1 == item2);
	}

};

/* Last Results:
Time(micro sec) Set Get(Ifel):      16005
Time(micro sec) Class Public(Ifel): 17757
Time(micro sec) Struct Func(Ifel):  14725
Time(micro sec) Free(Ifel):         16511
Time(micro sec) Struct(Ifel):       14728

Time(micro sec) Set Get(bool):      3366
Time(micro sec) Class Public(bool): 3342
Time(micro sec) Struct Func(bool):  1306
Time(micro sec) Free(bool):         1108
Time(micro sec) Struct(bool):       526
*/
TEST(Fastest, IfElseVsBoolean)
{
	TestPointSetGet classSetGet = TestPointSetGet(1, 1);
	TestPointPublic classPublic = TestPointPublic(1, 1);
	TestStruct structNormal = { 1, 1 };
	TestStructFunc structFunc = { 1, 1 };
	/* Free floating */
	unsigned short posx = 1;
	unsigned short posy = 1;
	int times = 2000000;

	/* Class Set Get  */
	auto start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			classSetGet.SetX(classSetGet.GetX() + (GameState::Move::Right == (GameState::Move)moveNmbr));
			classSetGet.SetX(classSetGet.GetX() - (GameState::Move::Left == (GameState::Move)moveNmbr));
			classSetGet.SetY(classSetGet.GetY() - (GameState::Move::Down == (GameState::Move)moveNmbr));
			classSetGet.SetY(classSetGet.GetY() + (GameState::Move::Up == (GameState::Move)moveNmbr));
		}
		if (classSetGet.GetX() != classSetGet.GetY())
		{
			std::cout << "Set Get(bool) error \n ";
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto durationSetGetBool = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			if (GameState::Move::Up == (GameState::Move)moveNmbr)
			{
				classSetGet.SetX(classSetGet.GetX() + 1);
			}
			else if (GameState::Move::Down == (GameState::Move)moveNmbr)
			{
				classSetGet.SetX(classSetGet.GetX() - 1);
			}
			else if (GameState::Move::Left == (GameState::Move)moveNmbr)
			{
				classSetGet.SetY(classSetGet.GetY() - 1);
			}
			else
			{
				classSetGet.SetY(classSetGet.GetY() + 1);
			}
		}
		if (classSetGet.GetX() != classSetGet.GetY())
		{
			std::cout << "Set Get(Ifel) error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationSetGetIfel = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);



	/* Class Public  */
	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			classPublic.X += (GameState::Move::Right == (GameState::Move)moveNmbr);
			classPublic.X -= (GameState::Move::Left == (GameState::Move)moveNmbr);
			classPublic.Y -= (GameState::Move::Down == (GameState::Move)moveNmbr);
			classPublic.Y += (GameState::Move::Up == (GameState::Move)moveNmbr);
		}
		if (classPublic.X != classPublic.Y)
		{
			std::cout << "Class Public error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationPublicBool = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			if (GameState::Move::Up == (GameState::Move)moveNmbr)
			{
				classPublic.X += 1;
			}
			else if (GameState::Move::Down == (GameState::Move)moveNmbr)
			{
				classPublic.X -= 1;
			}
			else if (GameState::Move::Left == (GameState::Move)moveNmbr)
			{
				classPublic.Y -= 1;
			}
			else
			{
				classPublic.Y += 1;
			}
		}
		if (classPublic.X != classPublic.Y)
		{
			std::cout << "Class Public error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationPublicIfel = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);



	/* Struct W/ Func  */
	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			structFunc.X += (GameState::Move::Right == (GameState::Move)moveNmbr);
			structFunc.X -= (GameState::Move::Left == (GameState::Move)moveNmbr);
			structFunc.Y -= (GameState::Move::Down == (GameState::Move)moveNmbr);
			structFunc.Y += (GameState::Move::Up == (GameState::Move)moveNmbr);
		}
		if (structFunc.X != structFunc.Y)
		{
			std::cout << "Struct Func error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationStructFuncBool = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			if (GameState::Move::Up == (GameState::Move)moveNmbr)
			{
				structFunc.X += 1;
			}
			else if (GameState::Move::Down == (GameState::Move)moveNmbr)
			{
				structFunc.X -= 1;
			}
			else if (GameState::Move::Left == (GameState::Move)moveNmbr)
			{
				structFunc.Y -= 1;
			}
			else
			{
				structFunc.Y += 1;
			}
		}
		if (structFunc.X != structFunc.Y)
		{
			std::cout << "Struct Func error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationStructFuncIfel = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);



	/* Normal Struct */
	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			structNormal.X += (GameState::Move::Right == (GameState::Move)moveNmbr);
			structNormal.X -= (GameState::Move::Left == (GameState::Move)moveNmbr);
			structNormal.Y -= (GameState::Move::Down == (GameState::Move)moveNmbr);
			structNormal.Y += (GameState::Move::Up == (GameState::Move)moveNmbr);
		}
		if (structNormal.X != structNormal.Y)
		{
			std::cout << "Struct Normal error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationStructNBool = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			if (GameState::Move::Up == (GameState::Move)moveNmbr)
			{
				structNormal.X += 1;
			}
			else if (GameState::Move::Down == (GameState::Move)moveNmbr)
			{
				structNormal.X -= 1;
			}
			else if (GameState::Move::Left == (GameState::Move)moveNmbr)
			{
				structNormal.Y -= 1;
			}
			else
			{
				structNormal.Y += 1;
			}
		}
		if (structNormal.X != structNormal.Y)
		{
			std::cout << "Struct Normal error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationStructNIfel = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);



	/* Free Float */
	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			posx += (GameState::Move::Right == (GameState::Move)moveNmbr);
			posx -= (GameState::Move::Left == (GameState::Move)moveNmbr);
			posy -= (GameState::Move::Down == (GameState::Move)moveNmbr);
			posy += (GameState::Move::Up == (GameState::Move)moveNmbr);
		}
		if (posx != posy)
		{
			std::cout << "Free float error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationFreeBool = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			if (GameState::Move::Up == (GameState::Move)moveNmbr)
			{
				posx += 1;
			}
			else if (GameState::Move::Down == (GameState::Move)moveNmbr)
			{
				posx -= 1;
			}
			else if (GameState::Move::Left == (GameState::Move)moveNmbr)
			{
				posy -= 1;
			}
			else
			{
				posy += 1;
			}
		}
		if (posx != posy)
		{
			std::cout << "Free float error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationFreeIfel = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time(micro sec) Set Get(Ifel):      " << durationSetGetIfel.count()  << "\n";
	std::cout << "Time(micro sec) Class Public(Ifel): " << durationPublicIfel.count() << "\n";
	std::cout << "Time(micro sec) Struct Func(Ifel):  " << durationStructFuncIfel.count() << "\n";
	std::cout << "Time(micro sec) Free(Ifel):         " << durationFreeIfel.count() << "\n";
	std::cout << "Time(micro sec) Struct(Ifel):       " << durationStructNIfel.count() << "\n";
	std::cout << "\n";
	std::cout << "Time(micro sec) Set Get(bool):      " << durationSetGetBool.count()  << "\n";
	std::cout << "Time(micro sec) Class Public(bool): " << durationPublicBool.count()  << "\n";
	std::cout << "Time(micro sec) Struct Func(bool):  " << durationStructFuncBool.count()  << "\n";
	std::cout << "Time(micro sec) Free(bool):         " << durationFreeBool.count() << "\n";
	std::cout << "Time(micro sec) Struct(bool):       " << durationStructNBool.count()  << "\n";



	TestPointPublic structFuncTest = { 1, 1 };
	EXPECT_EQ(classSetGet, TestPointSetGet(1,1));
	EXPECT_EQ(classPublic, TestPointPublic(1, 1));
	EXPECT_EQ(structFunc.X, structFuncTest.X);
	EXPECT_EQ(structFunc.Y, structFuncTest.Y);
	EXPECT_EQ(posx, posy);
	EXPECT_TRUE(TestStruct_Equal(structNormal, {1, 1}));
}

TestStruct structNormal = { 1, 1 };
TestStructFunc structFunc = { 1, 1 };
TestStruct structNormalRef = { 1, 1 };
TestStructFunc structFuncRef = { 1, 1 };
int times = 2000000;

/* Last Results:
Time(micro sec) Struct:      3014
Time(micro sec) Struct Func: 2807
*/
TEST(Fastest, ComparingCointainers)
{
	auto start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			structFunc.X += (GameState::Move::Right == (GameState::Move)moveNmbr);
			structFunc.X -= (GameState::Move::Left == (GameState::Move)moveNmbr);
			structFunc.X -= (GameState::Move::Down == (GameState::Move)moveNmbr);
			structFunc.X += (GameState::Move::Up == (GameState::Move)moveNmbr);
		}
		if (structFunc != structFuncRef)
		{
			std::cout << "Set Get(bool) error \n ";
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto durationstructFunc = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	start = std::chrono::high_resolution_clock::now();
	for (int counter = 0; counter < times; counter++)
	{
		for (int moveNmbr = 0; moveNmbr < (int)GameState::Move::Count; ++moveNmbr)
		{
			structNormal.X += (GameState::Move::Right == (GameState::Move)moveNmbr);
			structNormal.X -= (GameState::Move::Left == (GameState::Move)moveNmbr);
			structNormal.X -= (GameState::Move::Down == (GameState::Move)moveNmbr);
			structNormal.X += (GameState::Move::Up == (GameState::Move)moveNmbr);
		}
		if (!TestStruct_Equal(structNormal, structNormalRef))
		{
			std::cout << "Set Get(bool) error \n ";
		}
	}
	stop = std::chrono::high_resolution_clock::now();
	auto durationstruct = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time(micro sec) Struct:      " << durationstruct.count() << "\n";
	std::cout << "Time(micro sec) Struct Func: " << durationstructFunc.count() << "\n";

	TestPointPublic structFuncTest = { 1, 1 };
	EXPECT_EQ(structFunc.X, structFuncTest.X);
	EXPECT_EQ(structFunc.Y, structFuncTest.Y);
	EXPECT_TRUE(TestStruct_Equal(structNormal, { 1, 1 }));
}
