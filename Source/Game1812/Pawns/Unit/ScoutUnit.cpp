#include "ScoutUnit.h"

#include "UnitOrder.h"
#include "../../Actors/FogOfWar.h"
#include "../../Actors/HeadQuarters.h"
#include "Components/UnitMovementComponent.h"

AScoutUnit::AScoutUnit() 
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(FName("Movement Component"));

	MovementSpeed = 100;
	RotationSpeed = 160;
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
		if (OnMovementEnd.IsBound())
			OnMovementEnd.Broadcast();

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

float AScoutUnit::PredictMovementTime()
{
	if (ExplorationLocations.IsEmpty())
		return 0.0f;

	float totalDistance = 0.0f;

	TArray<FVector> savedLocations;

	do
	{
		FVector location;

		ExplorationLocations.Dequeue(location);

		if (savedLocations.IsEmpty()) 
		{
			totalDistance += FVector::Dist2D(GetActorLocation(), location);
		}
		else 
		{
			totalDistance += FVector::Dist2D(savedLocations.Last(), location);
		}

		savedLocations.Add(location);
	} 
	while (!ExplorationLocations.IsEmpty());

	for (FVector el : savedLocations) 
	{
		ExplorationLocations.Enqueue(el);
	}

	return totalDistance / GetMovementSpeed();
}

void AScoutUnit::OnOrderAssign(const FUnitOrder& NewOrder)
{
	if (MovementComponent->IsMoving())
		return;

	for (const FVector& location : CurrentOrder.ExplorationLocations)
	{
		ExplorationLocations.Enqueue(location);
	}

	ExplorationLocations.Enqueue(AHeadQuarters::GetSingleton()->GetActorLocation());

	if (OnMovementStart.IsBound())
		OnMovementStart.Broadcast();

	FVector firstLocation;
	ExplorationLocations.Dequeue(firstLocation);
	MovementComponent->SetTargetLocation(firstLocation);
}

UUnitMovementComponent* AScoutUnit::GetMovementComponent()
{
	return MovementComponent;
}

float AScoutUnit::GetMovementSpeed()
{
	return MovementSpeed;
}

float AScoutUnit::GetRotationSpeed()
{
	return RotationSpeed;
}
