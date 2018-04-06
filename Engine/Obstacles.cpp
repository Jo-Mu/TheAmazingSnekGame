#include "Obstacles.h"

void Obstacles::EnemyBlocks::Activate()
{
	isActive = true;
}

void Obstacles::EnemyBlocks::SetDeltaVelocity(int xv, int yv)
{
	xVelocity = xv;
	yVelocity = yv;
	deltaVelocitySet = true;
}

void Obstacles::EnemyBlocks::Move()
{
	if (deltaVelocitySet)
	{
		loc.x += xVelocity;
		loc.y += yVelocity;
	}
}

void Obstacles::EnemyBlocks::BorderClamp(const Board & brd)
{
	if (loc.x < 0)
	{
		loc.x = 0;
		xVelocity *= -1;
	}
	else if (loc.x >= brd.GetWidth())
	{
		loc.x = brd.GetWidth() - 1;
		xVelocity *= -1;
	}

	if (loc.y < 0)
	{
		loc.y = 0;
		yVelocity *= -1;
	}
	else if (loc.y >= brd.GetHeight())
	{
		loc.y = brd.GetHeight() - 1;
		yVelocity *= -1;
	}
}

void Obstacles::EnemyBlocks::Draw(Board & brd) const
{
	brd.DrawCell(loc, blockColor);
}


bool Obstacles::EnemyBlocks::GetIsActive() const
{
	return isActive;
}

bool Obstacles::AllBlocksActive()
{
	for(int i = 0; i < maxEnemyBlocks; i++)
	{
		if(!enemyBlocks[i].GetIsActive())
		{
			return false;
		}
	}

	return true;
}

void Obstacles::MoveBlocks(Board& brd)
{
	for (int i = 0; i < maxEnemyBlocks; i++) 
	{
		brd.LeaveObstacleSpace(enemyBlocks[i].loc);

		enemyBlocks[i].Move();
		enemyBlocks[i].BorderClamp(brd);

		brd.OccupyObstacleSpace(enemyBlocks[i].loc);
	}
}

void Obstacles::SpawnBlock(std::mt19937& rng, Board& brd, const Snake& snek, const Goal& goal)
{
	if (nEnemyBlocks < maxEnemyBlocks)
	{
		std::uniform_int_distribution<int> xDist(0, (brd.GetWidth() - 1));
		std::uniform_int_distribution<int> yDist(0, (brd.GetHeight() - 1));

		nEnemyBlocks++;
		enemyBlocks[nEnemyBlocks - 1].Activate();
		Location newLoc;
		do
		{
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while (snek.IsInTile(newLoc) || goal.IsInTile(newLoc) || brd.GetIsObstacleThere(newLoc));

		enemyBlocks[nEnemyBlocks - 1].loc = newLoc;
		brd.OccupyObstacleSpace(newLoc);
	}
}

void Obstacles::SpawnBlock(std::mt19937& rng, Board& brd, const Snake& sneker1, const Snake& sneker2, const Goal& goal)
{
	if (nEnemyBlocks < maxEnemyBlocks)
	{
		std::uniform_int_distribution<int> xDist(0, (brd.GetWidth() - 1));
		std::uniform_int_distribution<int> yDist(0, (brd.GetHeight() - 1));

		nEnemyBlocks++;
		enemyBlocks[nEnemyBlocks - 1].Activate();
		Location newLoc;
		do
		{
			newLoc.x = xDist(rng);
			newLoc.y = yDist(rng);
		} while (sneker1.IsInTile(newLoc) || sneker2.IsInTile(newLoc) || goal.IsInTile(newLoc) || brd.GetIsObstacleThere(newLoc));

		enemyBlocks[nEnemyBlocks - 1].loc = newLoc;
		brd.OccupyObstacleSpace(newLoc);
	}
}

void Obstacles::Draw(Board & brd)
{
	for(int i = 0; i < nEnemyBlocks; i++)
	{
			enemyBlocks[i].Draw(brd);
	}
}

void Obstacles::TriggerCrissCrossMovement()
{
	bool xVelocitySwitch = false;
	bool yVelocitySwitch = false;

	for(int i = 0; i < maxEnemyBlocks; i++)
	{
		if((i + 1) % 2 == 0)
		{
			yVelocitySwitch = !yVelocitySwitch;

			if (yVelocitySwitch)
			{
				enemyBlocks[i].SetDeltaVelocity(0, 1);
			}
			else
			{
				enemyBlocks[i].SetDeltaVelocity(0, -1);
			}
		}
		else
		{
			xVelocitySwitch = !xVelocitySwitch;

			if (xVelocitySwitch)
			{
				enemyBlocks[i].SetDeltaVelocity(1, 0);
			}
			else
			{
				enemyBlocks[i].SetDeltaVelocity(-1, 0);
			}
		}
	}
}

void Obstacles::TriggerRandomMovement(std::mt19937 rng)
{
	std::uniform_int_distribution<int> xDist(-1, 1);
	std::uniform_int_distribution<int> yDist(-1, 1);

	for(int i = 0; i < maxEnemyBlocks; i++)
	{
		enemyBlocks[i].SetDeltaVelocity(xDist(rng), yDist(rng));
	}
}
