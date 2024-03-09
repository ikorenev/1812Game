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

	SetCombatUnitType(CombatUnitType);
}

void ACombatUnit::SetCombatUnitType(ECombatUnitType NewCombatUnitType)
{
	CombatUnitType = NewCombatUnitType;

	UCossacksGameInstance* gameInstance = GetGameInstance<UCossacksGameInstance>();

	if (!gameInstance)
		return;

	FCombatUnitContainer combatUnitContainer = gameInstance->GetTeamUnitsTable(Team)->FindUnitStatsByType(CombatUnitType);
	CombatUnitStats = combatUnitContainer.UnitStats;
	CombatComponent->Init(CombatUnitStats);
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
}

FCombatUnitStats* ACombatUnit::GetCombatUnitStats()
{
	return (CombatUnitData) ? (&CombatUnitData->GetCombatUnitStats()) : nullptr;
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
	return CombatUnitStats.MovementSpeed;
}

float ACombatUnit::GetRotationSpeed()
{
	return CombatUnitStats.RotationSpeed;
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
