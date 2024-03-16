#include "AdjutantUnit.h"

#include "AssignedUnitOrder.h"
#include "UnitOrder.h"
#include "Components/UnitMovementComponent.h"
#include "../../Actors/HeadQuarters.h"

AAdjutantUnit::AAdjutantUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(FName("Movement Component"));

	MovementSpeed = 100.f;
	RotationSpeed = 160.f;

	MinDistanceToGiveOrder = 15.f;

	DeathCooldown = 15.f;
}

void AAdjutantUnit::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->OnMovementEnd.AddDynamic(this, &AAdjutantUnit::OnMovementComplete);
}

void AAdjutantUnit::AssignOrder(UUnitOrder* NewOrder)
{
	if (IsOnDeathCooldown())
		return;

	CurrentOrder = Cast<UAdjutantUnitOrder>(NewOrder);

	if (!CurrentOrder)
		return;

	Orders = TArray<FAssignedCombatUnitOrder>(CurrentOrder->SentOrdersToUnits);
	MoveToNextTarget();
}

void AAdjutantUnit::OnMovementComplete()
{
	if (IsOnDeathCooldown())
		return;

	if (Orders.IsEmpty())
	{
		AHeadQuarters* headQuarters = AHeadQuarters::GetInstance();

		if (!headQuarters)
			return;

		if (IsInReachToInteractWithActor(headQuarters)) 
		{
			headQuarters->AddAdjutantUnit(this);
			return;
		}

		MovementComponent->MoveTo(headQuarters->GetActorLocation(), true);
		return;
	}

	FAssignedCombatUnitOrder closestTarget = FindClosestTarget();

	if (IsInReachToInteractWithActor(closestTarget.Unit.Get()))
	{
		closestTarget.Unit->AssignOrder(closestTarget.UnitOrder);
		Orders.Remove(closestTarget);
	}

	MoveToNextTarget();
}

void AAdjutantUnit::MoveToNextTarget()
{
	if (Orders.IsEmpty()) 
	{
		AHeadQuarters* headQuarters = AHeadQuarters::GetInstance();

		if (!headQuarters)
			return;

		MovementComponent->MoveTo(headQuarters->GetActorLocation(), true);
		return;
	}

	MovementComponent->MoveTo(FindClosestTarget().Unit->GetActorLocation(), true);
}

FAssignedCombatUnitOrder AAdjutantUnit::FindClosestTarget()
{
	FAssignedCombatUnitOrder closestUnit = Orders[0];

	for (int i = 0; i < Orders.Num(); i++)
	{
		if (!Orders[i].Unit.IsValid())
		{
			Orders.RemoveAt(i);
			i--;
			continue;
		}

		if (FVector::DistSquared2D(GetActorLocation(), Orders[i].Unit->GetActorLocation()) < FVector::DistSquared2D(GetActorLocation(), closestUnit.Unit->GetActorLocation()))
		{
			closestUnit = Orders[i];
		}
	}

	return closestUnit;
}

bool AAdjutantUnit::IsOnDeathCooldown()
{
	return GetWorldTimerManager().IsTimerActive(DeathCooldownTimer);
}

bool AAdjutantUnit::IsInReachToInteractWithActor(AActor* Actor)
{
	if (!Actor)
		return false;

	return FVector::DistSquared2D(GetActorLocation(), Actor->GetActorLocation()) < FMath::Pow(MinDistanceToGiveOrder, 2);
}

void AAdjutantUnit::ApplyDamage(IDamageable* Attacker, float Amount)
{
	if (Amount < 1.f)
		return;

	ForceReturnToHQ();
	return;
}

void AAdjutantUnit::ForceReturnToHQ()
{
	AHeadQuarters* headQuarters = AHeadQuarters::GetInstance();

	if (!headQuarters)
	{
		Destroy();
		return;
	}

	headQuarters->RemoveAdjutantUnit(this);
	GetWorldTimerManager().SetTimer(DeathCooldownTimer, this, &AAdjutantUnit::OnDeathCooldownEnd, DeathCooldown);

	Orders.Empty();
	SetActorLocation(headQuarters->GetActorLocation());
	MovementComponent->StopMoving();
}

void AAdjutantUnit::OnDeathCooldownEnd()
{
	AHeadQuarters* headQuarters = AHeadQuarters::GetInstance();

	if (headQuarters)
		headQuarters->AddAdjutantUnit(this);
}

ETeam AAdjutantUnit::GetTeam()
{
	return Team;
}

ECombatUnitType AAdjutantUnit::GetUnitType()
{
	return ECombatUnitType::Cavalry;
}

FVector AAdjutantUnit::GetLocation()
{
	return GetActorLocation();
}

bool AAdjutantUnit::IsValidTarget()
{
	return !IsOnDeathCooldown();
}

UUnitOrder* AAdjutantUnit::GetCurrentOrder()
{
	return nullptr;
}

UUnitMovementComponent* AAdjutantUnit::GetMovementComponent()
{
	return MovementComponent;
}

float AAdjutantUnit::GetMovementSpeed()
{
	return MovementSpeed;
}

float AAdjutantUnit::GetRotationSpeed()
{
	return RotationSpeed;
}


