#include "CombatUnit.h"

#include "UnitOrder.h"
#include "Components/UnitMovementComponent.h"
#include "Components/CombatComponent.h"

ACombatUnit::ACombatUnit()
{
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(FName("Combat Component"));
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

void ACombatUnit::ApplyDamage(float Amount)
{

}

ETeam ACombatUnit::GetTeam()
{
	return Team;
}

bool ACombatUnit::IsDead()
{
	return false;
}

FVector ACombatUnit::GetLocation()
{
	return GetActorLocation();
}
