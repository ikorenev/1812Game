#include "Piece.h"

#include <Components/StaticMeshComponent.h>

APiece::APiece()
{
	PrimaryActorTick.bCanEverTick = true;

	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piece Mesh"));
	RootComponent = PieceMesh;

	PieceMesh->SetSimulatePhysics(true);

	IsBeingDragged = false;
	HoverHeight = 10;
	SweepCastHeight = 200;
}

void APiece::BeginPlay()
{
	Super::BeginPlay();
	
}

void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsBeingDragged) 
	{
		FVector newLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation + FVector(0, 0, HoverHeight), DeltaTime, 20);

		FHitResult hit;

		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(this);

		GetWorld()->SweepSingleByProfile(hit, newLocation + FVector(0, 0, SweepCastHeight), newLocation - FVector(0, 0, HoverHeight), GetActorQuat(), "BlockAll", PieceMesh->GetCollisionShape(), collisionParams);

		if (hit.bBlockingHit) 
		{
			newLocation = hit.Location + FVector(0, 0, HoverHeight);
		}

		SetActorLocation(newLocation);
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(0, GetActorRotation().Yaw, 0), DeltaTime, 20));
	}
}

void APiece::OnDragStart() 
{
	IsBeingDragged = true;
	PieceMesh->SetSimulatePhysics(false);
	TargetLocation = GetActorLocation();
}

void APiece::OnDragEnd() 
{
	IsBeingDragged = false;
	PieceMesh->SetSimulatePhysics(true);
}

void APiece::OnMouseMove(FVector location)
{
	TargetLocation = location;
}