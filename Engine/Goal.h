#pragma once

#include "Snake.h"
#include "Board.h"
#include "Colors.h"
#include "Location.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& rng, Board& brd, const Snake& sneker1, const Snake& sneker2);
	bool IsInTile(const Location& target) const;
	void Respawn(std::mt19937& rng, Board& brd, const Snake& snek);
	void Respawn(std::mt19937& rng, Board& brd, const Snake& sneker1, const Snake& sneker2);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;
private:
	Location loc;
	static constexpr Color c = Colors::Yellow;
};
