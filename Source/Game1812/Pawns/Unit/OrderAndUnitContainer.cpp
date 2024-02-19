#include "OrderAndUnitContainer.h"

FOrderAndUnitContainer::FOrderAndUnitContainer()
{
	Unit = nullptr;
}

FOrderAndUnitContainer::FOrderAndUnitContainer(const FUnitOrder& UnitOrder, ABaseUnit* Unit)
{
	this->UnitOrder = UnitOrder;
	this->Unit = Unit;
}

FOrderAndUnitContainer::~FOrderAndUnitContainer()
{
}

bool FOrderAndUnitContainer::operator==(const FOrderAndUnitContainer& Other)
{
	return (Unit == Other.Unit);
}
