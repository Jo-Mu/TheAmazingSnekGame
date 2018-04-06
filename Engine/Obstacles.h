#pragma once

#include "Colors.h"
#include "Location.h"
#include "Snake.h"
#include "Board.h"
#include "ActiveBlock.h"
#include <random>

class Obstacles 
{
private:
	class EnemyBlocks : public ActiveBlock
	{
	public:
		void SetDeltaVelocity(int xv, int yv);
		void Move();
		void BorderClamp(const Board& brd);
		void Draw(Board & brd) const;
	private:
		int xVelocity;
		int yVelocity;
		bool deltaVelocitySet = false;
		Color blockColor = Colors::Gray;

	};
public:
	void SpawnBlock(std::mt19937& rng, const Board& brd, const Snake& snek, const ActiveBlock& goal);
	void SpawnBlock(std::mt19937& rng, const Board& brd, const Snake& sneker1, const Snake& sneker2, const ActiveBlock& goal);
	bool IsInTile(const Location& target) const;
	void Draw(Board& brd);
	void TriggerCrissCrossMovement();
	void TriggerRandomMovement(std::mt19937 rng);
	bool AllBlocksActive();
	void MoveBlocks(const Board& brd);
private:
	static const int maxEnemyBlocks = 10;
	EnemyBlocks enemyBlocks[maxEnemyBlocks];
	int nEnemyBlocks = 0;
	Color blockColor = Colors::Gray;
	int blockCrissCrossSpeed = 1;
};