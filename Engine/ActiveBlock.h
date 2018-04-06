#pragma once
#include "Location.h"

class ActiveBlock
{
public:
	void Activate();
	bool IsInTile(const Location& target) const;
	bool GetIsActive() const;
	Location loc;
private:
	bool isActive = false;
};