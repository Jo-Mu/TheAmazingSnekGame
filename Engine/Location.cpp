#include "Location.h"

void Location::Add(const Location & val)
{
	x += val.x;
	y += val.y;
}

bool Location::operator==(const Location & loc) const
{
	return x == loc.x && y == loc.y;
}

bool Location::operator!=(const Location & loc) const
{
	return x != loc.x || y != loc.y;
}
