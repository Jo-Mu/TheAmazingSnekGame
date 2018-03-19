#include "Goal.h"
#include "Obstacles.h"

Goal::Goal(std::mt19937& rng, const Board& brd, const Snake& sneker1, const Snake& sneker2, const Obstacles& enemyBlocks)
{
	Respawn(rng, brd, sneker1, sneker2, enemyBlocks);
}

void Goal::Respawn(std::mt19937& rng, const Board& brd, const Snake& snek, const Obstacles& enemyBlocks)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snek.IsInTile(newLoc) || enemyBlocks.IsInTile(newLoc));

	loc = newLoc;
}

void Goal::Respawn(std::mt19937 & rng, const Board & brd, const Snake & sneker1, const Snake & sneker2, const Obstacles & enemyBlocks)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (sneker1.IsInTile(newLoc) || sneker2.IsInTile(newLoc) || enemyBlocks.IsInTile(newLoc));

	loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location & Goal::GetLocation() const
{
	return loc;
}

bool Goal::IsInTile(const Location& target) const
{
	return loc == target;
}
