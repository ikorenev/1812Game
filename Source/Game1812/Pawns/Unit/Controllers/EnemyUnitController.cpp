#include "EnemyUnitController.h"

#include "../CombatUnit.h"
#include "../UnitOrder.h"

AEnemyUnitController::AEnemyUnitController()
{
	
}

void AEnemyUnitController::OnPossess(APawn* InPawn)
{
	if (!InPawn)
		return;

	CombatUnit = Cast<ACombatUnit>(InPawn);
}
