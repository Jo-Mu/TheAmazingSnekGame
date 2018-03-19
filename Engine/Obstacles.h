#pragma once

#include "Colors.h"
#include "Location.h"
#include "Snake.h"
#include "Board.h"
#include <random>

class Goal;
class Obstacles 
{
private:
	class EnemyBlocks
	{
	public:
		void Activate();
		bool GetIsActive() const;
		void SetDeltaVelocity(int xv, int yv);
		void Move();
		void BorderClamp(const Board& brd);
		void Draw(Board & brd) const;
		bool IsInTile(const Location& target) const;
		Location loc;
	private:
		bool isActive = false;
		int xVelocity;
		int yVelocity;
		bool deltaVelocitySet = false;
		Color blockColor = Colors::Gray;

	};
public:
	void SpawnBlock(std::mt19937& rng, const Board& brd, const Snake& snek, const Goal& goal);
	void SpawnBlock(std::mt19937& rng, const Board& brd, const Snake& sneker1, const Snake& sneker2, const Goal& goal);
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