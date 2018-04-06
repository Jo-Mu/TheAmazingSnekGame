#include "ActiveBlock.h"

void ActiveBlock::Activate()
{
	isActive = true;
}

bool ActiveBlock::IsInTile(const Location& target) const
{
	return loc == target;
}

bool ActiveBlock::GetIsActive() const
{
	return isActive;
}
