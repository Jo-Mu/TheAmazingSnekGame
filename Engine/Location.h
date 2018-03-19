#pragma once

struct Location
{
	void Add(const Location& val);
	int x;
	int y;
	bool operator==(const Location& loc) const;
	bool operator!=(const Location& loc) const;
};