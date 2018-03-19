/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Location.h"
#include <random>
#include "Snake.h"
#include "SpriteCodex.h"
#include "Goal.h"
#include "Obstacles.h"
#include "FrameTimer.h"
class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	void PlaySinglePlayerGame(const float frameTime);
	void PlayMultiplayerGame(const float frameTime);
	void DrawSinglePlayerGame();
	void DrawMultiplayerGame();
	void SinglePlayerMovement();
	void MultiplayerPlayer1Movement();
	void MultiplayerPlayer2Movement();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	SpriteCodex sprites;
	Board brd;
	std::mt19937 rng;
	Snake sneker1;
	Snake sneker2;
	Location delta_loc1 = { 1, 0 };
	Location delta_loc2 = { -1, 0 };
	Obstacles obstacles;
	Goal goal;
	float snekMoveTimer = 0;
	float snekMovePeriod = .15;
	int headOnCollisionResult = 0;
	float enemySpawnTimer = 0;
	float secondsTillEnemySpawn = 5;
	float enemyMoveTimer = 0;
	float enemyMovePeriod = .15;
	float enemyPhaseTimer = 0;
	float secondsTillEnemyPhase2 = 40;
	bool enemyPhase1Triggered = false;
	bool enemyPhase2Triggered = false;
	bool startSinglePlayerGame = false;
	bool startMultiplayerGame = false;
	bool player1GameOver = false;
	bool player2GameOver = false;
	bool interval1 = false;
	bool interval2 = false;
	/********************************/
	/*  User Variables              */
	/********************************/
};