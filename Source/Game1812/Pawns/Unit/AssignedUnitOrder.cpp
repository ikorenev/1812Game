#include "AssignedUnitOrder.h"

#include "UnitOrder.h"

FAssignedUnitOrder::FAssignedUnitOrder()
{
	UnitOrder = nullptr;
	Unit = nullptr;
}

FAssignedUnitOrder::FAssignedUnitOrder(FUnitOrder UnitOrder, ABaseUnit* Unit)
{
	this->UnitOrder = new FUnitOrder();
	*this->UnitOrder = UnitOrder;
	this->Unit = Unit;
}

FAssignedUnitOrder::~FAssignedUnitOrder()
{
	delete this->UnitOrder;
}

FUnitOrder FAssignedUnitOrder::GetUnitOrder() const
{
	if (UnitOrder)
		return *UnitOrder;

	return FUnitOrder();
}

ABaseUnit* FAssignedUnitOrder::GetUnit() const
{
	return Unit;
}

bool FAssignedUnitOrder::operator==(const FAssignedUnitOrder& Other)
{
	return (Unit == Other.Unit);
}
