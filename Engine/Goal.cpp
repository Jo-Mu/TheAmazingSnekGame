#include "Goal.h"

Goal::Goal(std::mt19937& rng, Board& brd, const Snake& sneker1, const Snake& sneker2)
{
	Respawn(rng, brd, sneker1, sneker2);
}

bool Goal::IsInTile(const Location & target) const
{
	return loc == target;
}

void Goal::Respawn(std::mt19937& rng, Board& brd, const Snake& snek)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc) || brd.GetIsObstacleThere(newLoc));

	loc = newLoc;
}

void Goal::Respawn(std::mt19937& rng, Board& brd, const Snake& sneker1, const Snake& sneker2)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (sneker1.IsInTile(newLoc) || sneker2.IsInTile(newLoc) || brd.GetIsObstacleThere(newLoc));

	loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Goal::GetLocation() const
{
	return loc;
}
