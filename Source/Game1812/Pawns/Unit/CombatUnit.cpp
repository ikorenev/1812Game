#include "CombatUnit.h"

#include "UnitOrder.h"
#include "../../CossacksGameInstance.h"
#include "Components/UnitMovementComponent.h"

#include "Components/CombatComponent.h"

ACombatUnit::ACombatUnit()
{
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(FName("Combat Component"));

	CombatUnitType = ECombatUnitType::NONE;
}

void ACombatUnit::BeginPlay() 
{
	Super::BeginPlay();

	InitCombatUnitType(CombatUnitType);
}

void ACombatUnit::InitCombatUnitType(ECombatUnitType NewCombatUnitType)
{
	CombatUnitType = NewCombatUnitType;

	auto gameInstance = GetGameInstance<UCossacksGameInstance>();

	if (!gameInstance)
		return;

	FCombatUnitContainer combatUnitContainer = gameInstance->GetTeamUnitsTable(Team)->FindUnitStatsByType(CombatUnitType);

	CombatUnitStats = combatUnitContainer.UnitStats;

	CombatComponent->Init(CombatUnitStats);
}

float ACombatUnit::GetMovementSpeed()
{
	return CombatUnitStats.MovementSpeed;
}

float ACombatUnit::GetRotationSpeed()
{
	return CombatUnitStats.RotationSpeed;
}

FCombatUnitStats ACombatUnit::GetCombatUnitStats()
{
	return CombatUnitStats;
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
