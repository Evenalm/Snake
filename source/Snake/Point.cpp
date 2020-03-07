#include "point.h"
#include "limits.h"
#include "math.h"
#include <algorithm>

bool ArePointsEqual(Point const& item1, Point const& item2)
{
	return (item1.X == item2.X) && (item1.Y == item2.Y);
}

unsigned int GetManhattenDistance(Point item1, Point item2)
{
	return abs((int)item1.X - (int)item2.X) + abs((int)item1.Y - (int)item2.Y);
}