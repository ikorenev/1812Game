#include "ScoutPiece.h"

AScoutPiece::AScoutPiece()
{

}

void AScoutPiece::AssignOrder(FUnitOrder UnitOrder)
{
	Super::AssignOrder(UnitOrder);

	if (!Unit.IsValid())
		return;

	Unit->AssignOrder(UnitOrder);
}
