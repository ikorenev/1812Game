#include "AdjutantUnit.h"

#include "Components/UnitMovementComponent.h"
#include "../../Actors/HeadQuarters.h"

AAdjutantUnit::AAdjutantUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementSpeed = 100;
	RotationSpeed = 160;

	InteractionDistance = 15;
}

void AAdjutantUnit::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->OnMovementComplete.BindUObject(this, &AAdjutantUnit::OnMovementComplete);
}

void AAdjutantUnit::TaskOrders(const TArray<FOrderAndUnitContainer>& NewOrders)
{
	Orders = TArray<FOrderAndUnitContainer>(NewOrders);
	MoveToNextTarget();
}

void AAdjutantUnit::OnMovementComplete()
{
	if (Orders.IsEmpty())
	{
		AHeadQuarters* headQuarters = AHeadQuarters::GetSingleton();

		if (!headQuarters)
			return;

		if (FVector::DistSquared2D(GetActorLocation(), headQuarters->GetActorLocation()) > FMath::Pow(InteractionDistance, 2))
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

	if (FVector::DistSquared2D(GetActorLocation(), closestTarget.Unit->GetActorLocation()) > FMath::Pow(InteractionDistance, 2))
	{
		
		MoveToNextTarget();
	}
	else 
	{
		closestTarget.Unit->AssignOrder(closestTarget.UnitOrder);
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

	MovementComponent->SetTargetLocation(FindClosestTarget().Unit->GetActorLocation());
}

const FOrderAndUnitContainer& AAdjutantUnit::FindClosestTarget()
{
	FOrderAndUnitContainer* closestUnit = &Orders[0];

	for (auto el : Orders)
	{
		if (FVector::DistSquared2D(GetActorLocation(), el.Unit->GetActorLocation()) < FVector::DistSquared2D(GetActorLocation(), closestUnit->Unit->GetActorLocation()))
		{
			closestUnit = &el;
		}
	}

	return *closestUnit;
}

float AAdjutantUnit::GetMovementSpeed()
{
	return MovementSpeed;
}

float AAdjutantUnit::GetRotationSpeed()
{
	return RotationSpeed;
}
