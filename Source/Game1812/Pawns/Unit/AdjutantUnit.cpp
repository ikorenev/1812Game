#include "AdjutantUnit.h"

#include "UnitOrder.h"
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

	MovementComponent->OnMovementEnd.AddDynamic(this, &AAdjutantUnit::OnMovementComplete);
}

void AAdjutantUnit::AssignOrder(UUnitOrder* NewOrder)
{
	CurrentOrder = Cast<UAdjutantUnitOrder>(NewOrder);

	if (!CurrentOrder)
		return;

	Orders = TArray<FAssignedCombatUnitOrder>(CurrentOrder->SentOrdersToUnits);
	MoveToNextTarget();
}

void AAdjutantUnit::OnMovementComplete()
{
	if (Orders.IsEmpty())
	{
		AHeadQuarters* headQuarters = AHeadQuarters::GetInstance();

		if (!headQuarters)
			return;

		if (FVector::DistSquared2D(GetActorLocation(), headQuarters->GetActorLocation()) > FMath::Pow(MinDistanceToGiveOrder, 2))
		{
			MovementComponent->MoveTo(headQuarters->GetActorLocation(), true);
		}
		else 
		{
			headQuarters->AddAdjutantUnit(this);
		}

		return;
	}

	auto closestTarget = FindClosestTarget();

	if (FVector::DistSquared2D(GetActorLocation(), closestTarget.Unit->GetActorLocation()) > FMath::Pow(MinDistanceToGiveOrder, 2))
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

	for (auto el : Orders)
	{
		if (FVector::DistSquared2D(GetActorLocation(), el.Unit->GetActorLocation()) < FVector::DistSquared2D(GetActorLocation(), closestUnit.Unit->GetActorLocation()))
		{
			closestUnit = el;
		}
	}

	return closestUnit;
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
