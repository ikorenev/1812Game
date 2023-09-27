#include "Piece.h"

#include "../Pawns/BaseUnit.h"
#include "PaperMap.h"
#include <Components/StaticMeshComponent.h>

APiece::APiece()
{
	PrimaryActorTick.bCanEverTick = true;

	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piece Mesh"));
	RootComponent = PieceMesh;

	PieceMesh->SetSimulatePhysics(true);
	PieceMesh->SetNotifyRigidBodyCollision(true);

	IsBeingDragged = false;
	HoverHeight = 10;
	SweepCastHeight = 200;
}

void APiece::BeginPlay()
{
	Super::BeginPlay();
	
	PieceMesh->OnComponentHit.AddDynamic(this, &APiece::OnHit);
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

FVector APiece::FindPointOnMap()
{
	FHitResult hit;

	GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), GetActorLocation() - FVector(0, 0, 1000), ECollisionChannel::ECC_GameTraceChannel1);

	if (!hit.bBlockingHit) return FVector(0);

	return hit.Location;
}

void APiece::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) return;

	APaperMap* map = Cast<APaperMap>(OtherActor);

	if (!map) return;

	if (Unit) 
	{
		Unit->MoveToLocation(FindPointOnMap());
	}
	else 
	{
		FVector point = FindPointOnMap();

		if (point.IsNearlyZero()) return;

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Unit = GetWorld()->SpawnActor<ABaseUnit>(UnitClass.Get(), point, FRotator(0, 0, GetActorRotation().Yaw), spawnParams);
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