#include "EnemyUnitController.h"

#include "../Units/CombatUnit.h"
#include "../Orders/UnitOrder.h"

TArray<TWeakObjectPtr<AEnemyUnitController>> AEnemyUnitController::EnemyControllers = TArray<TWeakObjectPtr<AEnemyUnitController>>();

AEnemyUnitController::AEnemyUnitController()
{
	
}

void AEnemyUnitController::BeginPlay()
{
	Super::BeginPlay();

	EnemyControllers.Add(this);
}

void AEnemyUnitController::BeginDestroy()
{
	Super::BeginDestroy();

	EnemyControllers.Remove(this);
}


void AEnemyUnitController::OnPossess(APawn* InPawn)
{
	if (!InPawn)
		return;

	CombatUnit = Cast<ACombatUnit>(InPawn);
}

void AEnemyUnitController::FindAlliesInRange(TArray<AEnemyUnitController*> Allies, float Range)
{
	for (TWeakObjectPtr<AEnemyUnitController> controller : EnemyControllers) 
	{
		if (!controller.IsValid())
			continue;
	}

}

