#include "CombatUnit.h"

#include "UnitOrder.h"
#include "Components/UnitMovementComponent.h"

ACombatUnit::ACombatUnit()
{
}

void ACombatUnit::BeginPlay() 
{
	Super::BeginPlay();
}

void ACombatUnit::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	
}

void ACombatUnit::AssignOrder(FUnitOrder NewOrder)
{
	Super::AssignOrder(NewOrder);

	MovementComponent->SetTargetLocation(CurrentOrder.Location);
}