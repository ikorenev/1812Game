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

float ACombatUnit::GetMovementSpeed()
{
	return UnitStats.MovementSpeed;
}

float ACombatUnit::GetRotationSpeed()
{
	return UnitStats.RotationSpeed;
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

void ACombatUnit::ApplyDamage(UCombatComponent* Attacker, float Amount)
{
	CombatComponent->ApplyDamage(Attacker, Amount);
}

ETeam ACombatUnit::GetTeam()
{
	return Team;
}

bool ACombatUnit::IsDead()
{
	return CombatComponent->IsDead();
}

FVector ACombatUnit::GetLocation()
{
	return GetActorLocation();
}
