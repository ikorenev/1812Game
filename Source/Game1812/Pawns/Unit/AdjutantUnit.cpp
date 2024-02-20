#include "AdjutantUnit.h"

#include "Components/UnitMovementComponent.h"
#include "../../Actors/HeadQuarters.h"

AAdjutantUnit::AAdjutantUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(FName("Movement Component"));

	MovementSpeed = 100;
	RotationSpeed = 160;

	MinDistanceToGiveOrder = 15;
}

void AAdjutantUnit::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->OnMovementComplete.BindUObject(this, &AAdjutantUnit::OnMovementComplete);
}

void AAdjutantUnit::OnOrderAssign(const FUnitOrder& NewOrder)
{
	Orders = TArray<FAssignedUnitOrder>(NewOrder.SentOrdersToUnits);
	MoveToNextTarget();
}

void AAdjutantUnit::OnMovementComplete()
{
	if (Orders.IsEmpty())
	{
		AHeadQuarters* headQuarters = AHeadQuarters::GetSingleton();

		if (!headQuarters)
			return;

		if (FVector::DistSquared2D(GetActorLocation(), headQuarters->GetActorLocation()) > FMath::Pow(MinDistanceToGiveOrder, 2))
		{
			MovementComponent->SetTargetLocation(headQuarters->GetActorLocation());
		}
		else 
		{
			headQuarters->AddAdjutantUnit(this);
		}

		return;
	}

	auto closestTarget = FindClosestTarget();

	if (FVector::DistSquared2D(GetActorLocation(), closestTarget.GetUnit()->GetActorLocation()) > FMath::Pow(MinDistanceToGiveOrder, 2))
	{
		
		MoveToNextTarget();
	}
	else 
	{
		closestTarget.GetUnit()->AssignOrder(closestTarget.GetUnitOrder());
		Orders.Remove(closestTarget);

		MoveToNextTarget();
	}
}

void AAdjutantUnit::MoveToNextTarget()
{
	if (Orders.IsEmpty()) 
	{
		AHeadQuarters* headQuarters = AHeadQuarters::GetSingleton();

		if (!headQuarters)
			return;

		MovementComponent->SetTargetLocation(headQuarters->GetActorLocation());
		return;
	}

	MovementComponent->SetTargetLocation(FindClosestTarget().GetUnit()->GetActorLocation());
}

FAssignedUnitOrder AAdjutantUnit::FindClosestTarget()
{
	FAssignedUnitOrder closestUnit = Orders[0];

	for (auto el : Orders)
	{
		if (FVector::DistSquared2D(GetActorLocation(), el.GetUnit()->GetActorLocation()) < FVector::DistSquared2D(GetActorLocation(), closestUnit.GetUnit()->GetActorLocation()))
		{
			closestUnit = el;
		}
	}

	return closestUnit;
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
