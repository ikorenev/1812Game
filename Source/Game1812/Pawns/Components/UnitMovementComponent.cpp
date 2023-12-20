#include "UnitMovementComponent.h"

#include <NavigationPath.h>
#include <NavigationSystem.h>

#include "../BaseUnit.h"

UUnitMovementComponent::UUnitMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TargetLocation = FVector::ZeroVector;
	Moving = false;
}

void UUnitMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	UnitPawn = Cast<ABaseUnit>(GetOwner());

	if (!UnitPawn) DestroyComponent();

	TargetLocation = UnitPawn->GetActorLocation();
}

void UUnitMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Moving)
	{
		if (Path)
		{
			if (Path->IsValid())
			{
				UpdateMovement(DeltaTime);
			}
			else
			{
				CheckMovementComplete();
			}
		}

		UpdatePath();
	}
}

void UUnitMovementComponent::UpdateMovement(float DeltaTime) 
{
	FVector targetPoint = GetNextPathPoint();
	FVector movementDirection = (targetPoint - UnitPawn->GetActorLocation()).GetSafeNormal2D();

	const float rotationYaw = FQuat::FindBetween(UnitPawn->GetActorForwardVector(), movementDirection).Rotator().Yaw;

	RotateTo(DeltaTime, rotationYaw);

	//if (FMath::Abs(rotationYaw) < 5.0f)
		MoveTo(DeltaTime, targetPoint);

	CheckMovementComplete();
}

void UUnitMovementComponent::RotateTo(float DeltaTime, float RotationYaw)
{
	const float rotationDelta = FMath::Sign(RotationYaw) * DeltaTime * UnitPawn->GetRotationSpeed();
	const float limitedRotation = FMath::Clamp(rotationDelta, -FMath::Abs(RotationYaw), FMath::Abs(RotationYaw));

	UnitPawn->AddActorLocalRotation(FRotator(0, limitedRotation, 0));
}

void UUnitMovementComponent::MoveTo(float DeltaTime, FVector Location)
{
	const FVector delta = (Location - UnitPawn->GetActorLocation()) * FVector(1, 1, 0);
	const FVector direction = delta.GetSafeNormal();
	const FVector distance = direction * UnitPawn->GetMovementSpeed() * DeltaTime;

	if (distance.SizeSquared() > delta.SizeSquared())
	{
		UnitPawn->SetActorLocation(Location);
	}
	else
	{
		UnitPawn->AddActorWorldOffset(distance);
	}

	UnitPawn->AddActorWorldOffset(FVector(0, 0, 50));
	UnitPawn->AddActorWorldOffset(FVector(0, 0, -100), true);
}

void UUnitMovementComponent::SetTargetLocation(FVector NewTargetLocation)
{ 
	FHitResult hit;

	GetWorld()->LineTraceSingleByChannel(hit, NewTargetLocation, NewTargetLocation - FVector(0, 0, 2000.0f), ECollisionChannel::ECC_GameTraceChannel1);

	if (!hit.bBlockingHit) 
		return;
	
	TargetLocation = hit.Location;

	Moving = true;
	UpdatePath();

	CheckMovementComplete();
}

void UUnitMovementComponent::UpdatePath()
{
	if (Path)
	{
		Path->EnableDebugDrawing(false);
	}

	Path = UNavigationSystemV1::FindPathToLocationSynchronously(UnitPawn, UnitPawn->GetActorLocation(), TargetLocation, UnitPawn);

	if (Path) 
	{
		Path->EnableDebugDrawing(true);
	}
}

void UUnitMovementComponent::CheckMovementComplete()
{
	if (FVector::DistSquaredXY(GetLastPathPoint(), UnitPawn->GetActorLocation()) < 10.0f)
	{
		Moving = false;

		if (OnMovementComplete.IsBound())
			OnMovementComplete.Execute();
	}
}

FVector UUnitMovementComponent::GetNextPathPoint()
{
	if (!Path)
	{
		return UnitPawn->GetActorLocation();
	}

	for (FVector point : Path->PathPoints) 
	{
		if (!(FVector::DistSquared2D(UnitPawn->GetActorLocation(), point) < FMath::Pow(100.f, 2.f))) 
			return point;
	}

	return TargetLocation;
}

FVector UUnitMovementComponent::GetLastPathPoint() 
{
	if (!Path)
	{
		return UnitPawn->GetActorLocation();
	}
	
	return Path->PathPoints.Last();
}