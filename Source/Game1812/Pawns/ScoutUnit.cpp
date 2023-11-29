#include "ScoutUnit.h"

#include "UnitOrder.h"
#include "../Actors/HeadQuarters.h"
#include "Components/UnitMovementComponent.h"

AScoutUnit::AScoutUnit() 
{

}

void AScoutUnit::BeginPlay() 
{
	Super::BeginPlay();

	MovementComponent->OnMovementComplete.BindUObject(this, &AScoutUnit::OnMovementComplete);
}

void AScoutUnit::OnMovementComplete() 
{
	if (ExplorationLocations.IsEmpty())
		return;

	FVector location;
	ExplorationLocations.Dequeue(location);
	MovementComponent->SetTargetLocation(location);
}

void AScoutUnit::AssignOrder(FUnitOrder NewOrder)
{
	if (!ExplorationLocations.IsEmpty())
		return;

	Super::AssignOrder(NewOrder);

	for (const FVector& location : CurrentOrder.ExplorationLocations) 
	{
		ExplorationLocations.Enqueue(location);
	}

	ExplorationLocations.Enqueue(AHeadQuarters::GetSingleton()->GetActorLocation());

	FVector firstLocation;
	ExplorationLocations.Dequeue(firstLocation);
	MovementComponent->SetTargetLocation(firstLocation);
}