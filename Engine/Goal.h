#pragma once

#include "Snake.h"
#include "Board.h"
#include "Colors.h"
#include "Location.h"
#include "ActiveBlock.h"
#include "Obstacles.h"
#include <random>

class Goal : public ActiveBlock
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snake& sneker1, const Snake& sneker2, const Obstacles& enemyBlocks);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snek, const Obstacles& enemyBlocks);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& sneker1, const Snake& sneker2, const Obstacles& enemyBlocks);
	void Draw(Board& brd) const;
private:
	static constexpr Color c = Colors::Yellow;
};
