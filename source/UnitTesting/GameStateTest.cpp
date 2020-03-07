#include "pch.h"
#include "GameState.h"

TEST(GameState, MakeIllegalMoveDown)
{
    GameState state = GameState();
    state.MakeMove(GameState::Move::Down);
	EXPECT_FALSE(state.IsLegalGame());
}

TEST(GameState, MakeIllegalMoveLeft)
{
    GameState state = GameState();
    state.MakeMove(GameState::Move::Left);
	EXPECT_FALSE(state.IsLegalGame());
}

TEST(GameState, GetNextPoint)
{
    Point test1 = {1, 2};
	Point test2 = { 1, 0 };
	Point test3 = { 0, 1 };
	Point test4 = { 2, 1 };
	EXPECT_TRUE(ArePointsEqual(test1, GetNextPoint({ 1, 1 }, GameState::Move::Up)));
	EXPECT_TRUE(ArePointsEqual(test2, GetNextPoint({ 1, 1 }, GameState::Move::Down)));
	EXPECT_TRUE(ArePointsEqual(test3, GetNextPoint({ 1, 1 }, GameState::Move::Left)));
	EXPECT_TRUE(ArePointsEqual(test4, GetNextPoint({ 1, 1 }, GameState::Move::Right)));
}