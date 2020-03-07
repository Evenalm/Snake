#ifndef POINT_H
#define POINT_H

struct Point
{
	unsigned short X;
	unsigned short Y;
};

bool ArePointsEqual(Point const& item1, Point const& item2);
unsigned int GetManhattenDistance(Point item1, Point item2);

#endif // POINT_H 
