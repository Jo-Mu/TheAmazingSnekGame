/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	sneker1({ 2, 2 }, 1),
	sneker2({brd.GetWidth() - 2, brd.GetHeight() - 2}, 2),
	goal(rng, brd, sneker1, sneker2, obstacles)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float frameTime = ft.Mark();

	if (startSinglePlayerGame) 
	{
		PlaySinglePlayerGame(frameTime);
	}
	else if(startMultiplayerGame)
	{
		PlayMultiplayerGame(frameTime);
	}
	else if(wnd.kbd.KeyIsPressed(VK_RETURN) || wnd.kbd.KeyIsPressed('1'))
	{
		startSinglePlayerGame = true;
	}
	else if(wnd.kbd.KeyIsPressed('2'))
	{
		startMultiplayerGame = true;
	}
}

void Game::ComposeFrame()
{
	if (startSinglePlayerGame) 
	{
		DrawSinglePlayerGame();
	}
	else if(startMultiplayerGame)
	{
		DrawMultiplayerGame();
	}
	else
	{
		sprites.DrawTitle(300, 200, gfx);
	}
}

void Game::PlaySinglePlayerGame(const float frameTime)
{
	if (!player1GameOver)
	{
		SinglePlayerMovement();
		snekMoveTimer += frameTime;

		if (!obstacles.AllBlocksActive()) 
		{
			enemySpawnTimer += frameTime;
		}

		if (enemyPhase1Triggered)
		{
			enemyMoveTimer += frameTime;
		}

		if (enemyPhase1Triggered && !enemyPhase2Triggered)
		{
			enemyPhaseTimer += frameTime;
		}

		if(enemyMoveTimer >= enemyMovePeriod)
		{
			enemyMoveTimer -= enemyMovePeriod;
			obstacles.MoveBlocks(brd);
		}

		if (snekMoveTimer >= snekMovePeriod)
		{
			snekMoveTimer -= snekMovePeriod;
			Location next = sneker1.GetNextLocation(delta_loc1);
			const bool eating = next == goal.loc;

			if (!brd.IsInsideBoard(next) || sneker1.IsInTileExceptEnd(next) || obstacles.IsInTile(next))
			{
				player1GameOver = true;
			}

			else
			{
				if (eating)
				{
					sneker1.Grow();
					goal.Respawn(rng, brd, sneker1, obstacles);
				}

				sneker1.MoveBy(delta_loc1);

				if (enemySpawnTimer >= secondsTillEnemySpawn)
				{
					obstacles.SpawnBlock(rng, brd, sneker1, goal);
					enemySpawnTimer -= secondsTillEnemySpawn;
				}
			}
			interval1 = false;
		}

		if (obstacles.AllBlocksActive() && !enemyPhase1Triggered)
		{
			obstacles.TriggerCrissCrossMovement();
			enemyPhase1Triggered = true;
		}

		if (enemyPhaseTimer >= secondsTillEnemyPhase2 && !enemyPhase2Triggered)
		{

			obstacles.TriggerRandomMovement(rng);
			enemyPhase2Triggered = true;
		}
	}
}

void Game::DrawSinglePlayerGame()
{
	if (!player1GameOver)
	{
		int starting = 100;
		for (int x = 0; x < brd.GetWidth(); x++)
		{
			for (int y = 0; y < brd.GetHeight(); y++)
			{
				Location loc;
				loc.x = x;
				loc.y = y;
				brd.DrawCell(loc, { 0, 0, 0 });
			}
		}
		brd.DrawBorder(Colors::Blue);
		goal.Draw(brd);
		obstacles.Draw(brd);
		sneker1.Draw(brd);
	}
	else
	{
		sprites.DrawGameOver(350, 275, gfx);
	}
}

void Game::PlayMultiplayerGame(const float frameTime)
{
	if (!player1GameOver && !player2GameOver)
	{
		MultiplayerPlayer1Movement();
		MultiplayerPlayer2Movement();
		snekMoveTimer += frameTime;

		if (!obstacles.AllBlocksActive())
		{
			enemySpawnTimer += frameTime;
		}

		if (enemyPhase1Triggered)
		{
			enemyMoveTimer += frameTime;
		}

		if (enemyPhase1Triggered && !enemyPhase2Triggered)
		{
			enemyPhaseTimer += frameTime;
		}

		if (enemyMoveTimer >= enemyMovePeriod)
		{
			enemyMoveTimer -= enemyMovePeriod;
			obstacles.MoveBlocks(brd);
		}

		if (snekMoveTimer >= snekMovePeriod)
		{
			snekMoveTimer -= snekMovePeriod;
			Location next1 = sneker1.GetNextLocation(delta_loc1);
			Location next2 = sneker2.GetNextLocation(delta_loc2);
			const bool eating1 = next1 == goal.loc;
			const bool eating2 = next2 == goal.loc;

			if (!brd.IsInsideBoard(next1) || sneker1.IsInTileExceptEnd(next1) || obstacles.IsInTile(next1) || sneker2.PlayerCollisionExceptHeadAndEnd(next1))
			{
				player1GameOver = true;
			}

			if (!brd.IsInsideBoard(next2) || sneker1.IsInTileExceptEnd(next2) || obstacles.IsInTile(next2) || sneker1.PlayerCollisionExceptHeadAndEnd(next2))
			{
				player2GameOver = true;
			}

			int headOnCollisionResult = sneker1.HeadOnCollision(next1, next2, sneker2);

			switch (headOnCollisionResult)
			{
			case 0: break;
			case 1: player2GameOver = true;
				break;
			case 2: player1GameOver = true;
				break;
			case 3: player1GameOver = true;
				player2GameOver = true;
				break;
			default: break;
			}

			if(!player1GameOver && !player2GameOver)
			{
				if (eating1)
				{
					sneker1.Grow();
					goal.Respawn(rng, brd, sneker1, sneker2, obstacles);
				}

				if (eating2)
				{
					sneker2.Grow();
					goal.Respawn(rng, brd, sneker1, sneker2, obstacles);
				}

				sneker1.MoveBy(delta_loc1);
				sneker2.MoveBy(delta_loc2);

				if (enemySpawnTimer >= secondsTillEnemySpawn)
				{
					obstacles.SpawnBlock(rng, brd, sneker1, sneker2, goal);
					enemySpawnTimer -= secondsTillEnemySpawn;
				}
			}
			interval1 = false;
			interval2 = false;
		}

		if (obstacles.AllBlocksActive() && !enemyPhase1Triggered)
		{
			obstacles.TriggerCrissCrossMovement();
			enemyPhase1Triggered = true;
		}

		if (enemyPhaseTimer >= secondsTillEnemyPhase2 && !enemyPhase2Triggered)
		{

			obstacles.TriggerRandomMovement(rng);
			enemyPhase2Triggered = true;
		}
	}
}

void Game::DrawMultiplayerGame()
{
	if (!player1GameOver && !player2GameOver)
	{
		int starting = 100;
		for (int x = 0; x < brd.GetWidth(); x++)
		{
			for (int y = 0; y < brd.GetHeight(); y++)
			{
				Location loc;
				loc.x = x;
				loc.y = y;
				brd.DrawCell(loc, { 0, 0, 0 });
			}
		}
		brd.DrawBorder(Colors::Blue);
		goal.Draw(brd);
		obstacles.Draw(brd);
		sneker1.Draw(brd);
		sneker2.Draw(brd);
	}
	else if(player1GameOver && player2GameOver)
	{
		sprites.DrawGameOver(350, 275, gfx);
		sneker1.Draw(brd);
		sneker2.Draw(brd);
	}
	else if(player1GameOver)
	{
		sprites.DrawGameOver(350, 275, gfx);
		sneker2.Draw(brd);
	}
	else
	{
		sprites.DrawGameOver(350, 275, gfx);
		sneker1.Draw(brd);
	}
}

void Game::SinglePlayerMovement()
{
	Location oppositeDirectionTest;

	if (wnd.kbd.KeyIsPressed(VK_UP) || wnd.kbd.KeyIsPressed('W'))
	{
		oppositeDirectionTest = { 0, 1 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { 0, -1 };
			interval1 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN) || wnd.kbd.KeyIsPressed('S'))
	{
		oppositeDirectionTest = { 0, -1 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { 0, 1 };
			interval1 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT) || wnd.kbd.KeyIsPressed('A'))
	{
		oppositeDirectionTest = { 1, 0 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { -1, 0 };
			interval1 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT) || wnd.kbd.KeyIsPressed('D'))
	{
		oppositeDirectionTest = { -1, 0 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { 1, 0 };
			interval1 = true;
		}
	}
}

void Game::MultiplayerPlayer1Movement()
{
	Location oppositeDirectionTest;

	if (wnd.kbd.KeyIsPressed('W'))
	{
		oppositeDirectionTest = { 0, 1 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { 0, -1 };
			interval1 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed('S'))
	{
		oppositeDirectionTest = { 0, -1 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { 0, 1 };
			interval1 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed('A'))
	{
		oppositeDirectionTest = { 1, 0 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { -1, 0 };
			interval1 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed('D'))
	{
		oppositeDirectionTest = { -1, 0 };

		if (delta_loc1 != oppositeDirectionTest && !interval1)
		{
			delta_loc1 = { 1, 0 };
			interval1 = true;
		}
	}
}

void Game::MultiplayerPlayer2Movement()
{
	Location oppositeDirectionTest;

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		oppositeDirectionTest = { 0, 1 };

		if (delta_loc2 != oppositeDirectionTest && !interval2)
		{
			delta_loc2 = { 0, -1 };
			interval2 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		oppositeDirectionTest = { 0, -1 };

		if (delta_loc2 != oppositeDirectionTest && !interval2)
		{
			delta_loc2 = { 0, 1 };
			interval2 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		oppositeDirectionTest = { 1, 0 };

		if (delta_loc2 != oppositeDirectionTest && !interval2)
		{
			delta_loc2 = { -1, 0 };
			interval2 = true;
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		oppositeDirectionTest = { -1, 0 };

		if (delta_loc2 != oppositeDirectionTest && !interval2)
		{
			delta_loc2 = { 1, 0 };
			interval2 = true;
		}
	}
}
