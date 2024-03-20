#include "CombatUnit.h"

#include "UnitOrder.h"

#include "Components/UnitMovementComponent.h"
#include "Components/UnitCombatComponent.h"
#include "Controllers/EnemyUnitController.h"
#include "CombatUnitDataAsset.h"

#include "../../CossacksGameInstance.h"

ACombatUnit::ACombatUnit()
{
	MovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(TEXT("Movement Component"));

	CombatComponent = CreateDefaultSubobject<UUnitCombatComponent>(TEXT("Combat Component"));

	CombatUnitData = nullptr;
}

void ACombatUnit::BeginPlay()
{
	Super::BeginPlay();

	if (!CombatUnitData)
		return;

	CombatComponent->Init(CombatUnitData->GetCombatUnitStats());
}

void ACombatUnit::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!CurrentOrder) 
	{
		CurrentOrder = NewObject<UCombatUnitOrder>();
		CurrentOrder->UnitEnemyReaction = EUnitEnemyReaction::Attack;
	}

	CurrentOrder->Location = GetActorLocation();
}

void ACombatUnit::SpawnDefaultController()
{
	if (GetTeam() == ETeam::France)
	{
		AEnemyUnitController* enemyUnitController = GetWorld()->SpawnActor<AEnemyUnitController>();

		if (enemyUnitController)
			enemyUnitController->Possess(this);
	}
}

void ACombatUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACombatUnit::AssignOrder(UUnitOrder* NewOrder)
{
	CurrentOrder = Cast<UCombatUnitOrder>(NewOrder);

	if (CurrentOrder)
		MovementComponent->MoveTo(CurrentOrder->Location, true);
}

void ACombatUnit::SetCombatUnitData(UCombatUnitDataAsset* NewCombatUnitData)
{
	CombatUnitData = NewCombatUnitData;

	if (!CombatUnitData)
		return;

	CombatComponent->Init(CombatUnitData->GetCombatUnitStats());
}

FUnitReport& ACombatUnit::GetUnitReport()
{
	return UnitReport;
}

FUnitReport ACombatUnit::RequestUnitReport()
{
	FUnitReport newUnitReport(UnitReport);
	UnitReport.Clear();

	newUnitReport.SetMorale(CombatComponent->GetMorale());

	return newUnitReport;
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
	return CombatComponent->CalculateMovementSpeed();
}

float ACombatUnit::GetRotationSpeed()
{
	return CombatComponent->CalculateRotationSpeed();
}

float ACombatUnit::ApplyDamage(IDamageable* Attacker, float Amount)
{
	return CombatComponent->ApplyDamage(Attacker, Amount);
}

ETeam ACombatUnit::GetTeam()
{
	return Team;
}

ECombatUnitType ACombatUnit::GetUnitType()
{
	return GetCombatUnitStats()->GetUnitType();
}

FVector ACombatUnit::GetLocation()
{
	return GetActorLocation();
}

bool ACombatUnit::IsValidTarget()
{
	return true;
}
