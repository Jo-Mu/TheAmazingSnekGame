#pragma once

#include "Snake.h"
#include "Board.h"
#include "Colors.h"
#include "Location.h"
#include <random>

class Obstacles;
class Goal
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& sneker1, const Snake& sneker2, const Obstacles& enemyBlocks);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snek, const Obstacles& enemyBlocks);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& sneker1, const Snake& sneker2, const Obstacles& enemyBlocks);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
	bool IsInTile(const Location& target) const;
private:
	static constexpr Color c = Colors::Yellow;
	Location loc;
};
