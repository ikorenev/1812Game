#include "ScoutPiece.h"

AScoutPiece::AScoutPiece()
{

}

void AScoutPiece::AssignOrder(UUnitOrder* UnitOrder)
{
	Super::AssignOrder(UnitOrder);

	if (!Unit.IsValid())
		return;

	Unit->AssignOrder(UnitOrder);
}
