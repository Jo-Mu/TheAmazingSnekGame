#include "Board.h"
#include <assert.h>

Board::Board(Graphics& in_gfx)
	:
	gfx(in_gfx)
{
}

void Board::DrawCell(const Location & loc, const Color c) const
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	gfx.DrawRectDim((loc.x * cellDimensions) + x_offset, (loc.y * cellDimensions) + y_offset, cellDimensions, cellDimensions, c);
}

void Board::DrawCellWithPadding(const Location & loc, int cellPadding, const Color c) const
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	gfx.DrawRectDim((loc.x * cellDimensions) + (x_offset + cellPadding), (loc.y * cellDimensions) + (y_offset + cellPadding), (cellDimensions - cellPadding), (cellDimensions - cellPadding), c);
}

void Board::DrawBorder(const Color c) const
{
	const int left = x_offset;
	const int right = (width * cellDimensions) + x_offset;
	const int top = y_offset;
	const int bottom = (height * cellDimensions) + y_offset;

	gfx.DrawRect((left - borderPadding), (top - borderPadding), left, (bottom + borderPadding), c);
	gfx.DrawRect(right, (top - borderPadding), (right + borderPadding), (bottom + borderPadding), c);
	gfx.DrawRect((left - borderPadding), (top - borderPadding), (right + borderPadding), top, c);
	gfx.DrawRect((left - borderPadding), bottom, (right + borderPadding), (bottom + borderPadding), c);
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 &&
		loc.x < width &&
		loc.y >= 0 &&
		loc.y < height;
}
