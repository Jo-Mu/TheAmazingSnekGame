#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc, int player1or2)
	:
	rng(std::random_device()())
{
	assert(player1or2 == 1 || player1or2 == 2);
	playerNum = player1or2;

	if (playerNum == 1) 
	{
		segments[0].InitHead(loc, headColor1);
	}
	else
	{
		segments[0].InitHead(loc, headColor2);
	}
}

Location Snake::GetNextLocation(const Location & delta_loc) const
{
	Location l = segments[0].GetLocation();
	l.Add(delta_loc);
	return l;
}

void Snake::MoveBy(const Location & delta_loc)
{
	for(int i = nSegments; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}

	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if(nSegments < nSegmentsMax)
	{
		nSegments++;
		if (playerNum == 1)
		{
			segments[nSegments - 1].InitBody(rng, bodyColor1);
		}
		else
		{
			segments[nSegments - 1].InitBody(rng, bodyColor2);
		}
	}
}

void Snake::Draw(Board& brd) const
{
	for(int i = 0; i < nSegments;i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location & target) const
{
	for(int i = 0; i < (nSegments - 1); i++)
	{
		if(segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < (nSegments); i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

bool Snake::PlayerCollisionExceptHeadAndEnd(const Location& snekerNextHeadLoc) const
{
	for (int i = 1; i < (nSegments - 1); i++)
	{
		if (segments[i].GetLocation() == snekerNextHeadLoc)
		{
			return true;
		}
	}

	return false;
}

int Snake::HeadOnCollision(const Location& sneker1NextHeadLoc, const Location& sneker2NextHeadLoc, const Snake& sneker2) const
{
	if(sneker1NextHeadLoc == sneker2NextHeadLoc)
	{
		if(nSegments > sneker2.nSegments)
		{
			return 1;
		}
		else if(nSegments < sneker2.nSegments)
		{
			return 2;
		}
		else if(nSegments == sneker2.nSegments)
		{
			return 3;
		}
	}

	return 0;
}

bool Snake::PlayerWon() const
{
	return nSegments == nSegmentsMax;
}

void Snake::Segment::InitHead(const Location& in_loc, const Color headColor)
{
	loc = in_loc;

	c = headColor;
}

void Snake::Segment::InitBody(std::mt19937& rng, const Color bodyColor)
{
	std::uniform_int_distribution<int> colorDist(0, 80);
	int r = bodyColor.GetR();
	int g = bodyColor.GetG();
	int b = bodyColor.GetB();
	
	if(r < 180)
	{
		r = colorDist(rng);
	}

	if (g < 180)
	{
		g = colorDist(rng);
	}

	if (b < 180)
	{
		b = colorDist(rng);
	}

	unsigned char ru = r;
	unsigned char gu = g;
	unsigned char bu = b;
	c = Color { ru, gu, bu };
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert((abs(delta_loc.x) + abs(delta_loc.y)) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCellWithPadding(loc, segmentPadding, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
