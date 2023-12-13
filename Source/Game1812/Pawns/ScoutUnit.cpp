#include "ScoutUnit.h"

#include "UnitOrder.h"
#include "../Actors/FogOfWar.h"
#include "../Actors/HeadQuarters.h"
#include "Components/UnitMovementComponent.h"

AScoutUnit::AScoutUnit() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void AScoutUnit::BeginPlay() 
{
	Super::BeginPlay();

	MovementComponent->OnMovementComplete.BindUObject(this, &AScoutUnit::OnMovementComplete);
}

void AScoutUnit::OnMovementComplete() 
{
	if (ExplorationLocations.IsEmpty())
	{
		AFogOfWar* fogOfWarActor = AFogOfWar::GetSingleton();

		if (!fogOfWarActor)
			return;

		fogOfWarActor->RevealChunks(ChunksToReveal.Array());
		ChunksToReveal.Empty();
	}

	FVector location;
	ExplorationLocations.Dequeue(location);
	MovementComponent->SetTargetLocation(location);
}

void AScoutUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementComponent->IsMoving())
	{
		AFogOfWar* fogOfWarActor = AFogOfWar::GetSingleton();

		if (!fogOfWarActor)
			return;

		const int ChuckRevealRange = 2;
		const FVector ChunkSize = fogOfWarActor->GetChunkSize();

		for (int x = -ChuckRevealRange + 1; x < ChuckRevealRange; x++) 
		{
			for (int y = -ChuckRevealRange + 1; y < ChuckRevealRange; y++)
			{
				ChunksToReveal.Add(fogOfWarActor->LocationToIndex(GetActorLocation() + ChunkSize * FVector(x, y, 0)));
			}
		}
	}
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