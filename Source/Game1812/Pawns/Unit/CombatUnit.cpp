#include "CombatUnit.h"

#include "UnitOrder.h"

#include "Components/UnitMovementComponent.h"
#include "Components/CombatComponent.h"
#include "CombatUnitDataAsset.h"

#include "../../CossacksGameInstance.h"

ACombatUnit::ACombatUnit()
{
	MovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(FName("Movement Component"));

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(FName("Combat Component"));

	CombatUnitData = nullptr;
}

void ACombatUnit::BeginPlay() 
{
	Super::BeginPlay();

	if (CombatUnitData)
		CombatComponent->Init(CombatUnitData->GetCombatUnitStats());
}

void ACombatUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACombatUnit::AssignOrder(UUnitOrder* NewOrder)
{
	CurrentOrder = Cast<UCombatUnitOrder>(NewOrder);

	if (CurrentOrder)
		MovementComponent->MoveTo(CurrentOrder->Location);
}

void ACombatUnit::SetCombatUnitData(UCombatUnitDataAsset* NewCombatUnitData)
{
	CombatUnitData = NewCombatUnitData;

	if (!CombatUnitData)
		return;

	CombatComponent->Init(CombatUnitData->GetCombatUnitStats());
}

FCombatUnitStats* ACombatUnit::GetCombatUnitStats()
{
	return CombatUnitData ? CombatUnitData->GetCombatUnitStats() : nullptr;
}

UUnitOrder* ACombatUnit::GetCurrentOrder()
{
	return CurrentOrder;
}

UUnitMovementComponent* ACombatUnit::GetMovementComponent()
{
	return MovementComponent;
}

float ACombatUnit::GetMovementSpeed()
{
	return GetCombatUnitStats() ? GetCombatUnitStats()->GetMovementSpeed() : 0.0f;
}

float ACombatUnit::GetRotationSpeed()
{
	return GetCombatUnitStats() ? GetCombatUnitStats()->GetRotationSpeed() : 0.0f;
}

void ACombatUnit::ApplyDamage(UCombatComponent* Attacker, float Amount)
{
	CombatComponent->ApplyDamage(Attacker, Amount);
}

ETeam ACombatUnit::GetTeam()
{
	return Team;
}

FVector ACombatUnit::GetLocation()
{
	return GetActorLocation();
}
