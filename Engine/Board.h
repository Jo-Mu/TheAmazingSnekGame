#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& in_gfx);
	void DrawCell(const Location& loc, const Color c) const;
	void DrawCellWithPadding(const Location& loc, int cellPadding, const Color c) const;
	void DrawBorder(const Color c) const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsInsideBoard(const Location& loc) const;
private:
	static constexpr int cellDimensions = 15;
	static constexpr int x_offset = 20;
	static constexpr int y_offset = 20;
	static constexpr int width = 50;
	static constexpr int height = 37;
	static constexpr int borderPadding = 5;
	Graphics& gfx;
};