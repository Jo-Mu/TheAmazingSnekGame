#pragma once

#include "Location.h"
#include "Colors.h"
#include "Board.h"
#include <random>

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc, const Color headColor);
		void InitBody(std::mt19937& rng, const Color bodyColor);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;
	private:
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc, int player1or2);
	Location loc;
	Location GetNextLocation(const Location& delta_loc) const;
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
	bool PlayerCollisionExceptHeadAndEnd(const Location& snekerNextHeadLoc) const;
	int HeadOnCollision(const Location& sneker1NextHeadLoc, const Location& sneker2NextHeadLoc, const Snake& sneker2) const;
private:
	static constexpr Color headColor1 = { 255,0,0 };
	static constexpr Color bodyColor1 = {0, 180, 0};
	static constexpr Color headColor2 = { 0,0,139 };
	static constexpr Color bodyColor2 = {180, 0, 0};
	static const int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	std::mt19937 rng;
	int nSegments = 1;
	int playerNum;
	static const int segmentPadding = 2;
};