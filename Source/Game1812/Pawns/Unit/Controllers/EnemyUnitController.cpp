#include "EnemyUnitController.h"

#include "../Units/CombatUnit.h"
#include "../Orders/UnitOrder.h"

AEnemyUnitController::AEnemyUnitController()
{
	
}

void AEnemyUnitController::OnPossess(APawn* InPawn)
{
	if (!InPawn)
		return;

	CombatUnit = Cast<ACombatUnit>(InPawn);
}
