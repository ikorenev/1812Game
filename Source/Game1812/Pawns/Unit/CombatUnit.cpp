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

void ACombatUnit::ApplyDamage(IDamageable* Attacker, float Amount)
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
