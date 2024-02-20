#include "AssignedUnitOrder.h"

FAssignedUnitOrder::FAssignedUnitOrder()
{
	Unit = nullptr;
}

FAssignedUnitOrder::FAssignedUnitOrder(const FUnitOrder& UnitOrder, ABaseUnit* Unit)
{
	this->UnitOrder = UnitOrder;
	this->Unit = Unit;
}

FAssignedUnitOrder::~FAssignedUnitOrder()
{
}

bool FAssignedUnitOrder::operator==(const FAssignedUnitOrder& Other)
{
	return (Unit == Other.Unit);
}
