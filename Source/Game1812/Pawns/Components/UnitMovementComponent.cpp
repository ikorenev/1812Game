#include "UnitMovementComponent.h"

#include <NavigationPath.h>
#include <NavigationSystem.h>

#include "../BaseUnit.h"

UUnitMovementComponent::UUnitMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TargetLocation = FVector::ZeroVector;
}

void UUnitMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	UnitPawn = Cast<ABaseUnit>(GetOwner());

	if (!UnitPawn) DestroyComponent();
}

void UUnitMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Path)
	{
		if ((TargetLocation - UnitPawn->GetActorLocation()).SizeSquared2D() < 1.0f) 
			return;

		UpdatePath();
	}

	if (Path) 
	{
		if (Path->IsValid()) 
			UpdateMovement(DeltaTime);

		UpdatePath();
	}
}

void UUnitMovementComponent::UpdateMovement(float DeltaTime) 
{
	FVector targetPoint = GetNextPathPoint();
	FVector movementDirection = (targetPoint - UnitPawn->GetActorLocation()).GetSafeNormal2D();

	if (movementDirection.IsNearlyZero()) 
	{
		//return;
	}

	GEngine->AddOnScreenDebugMessage(2, 10, FColor::Blue, *targetPoint.ToString());

	GEngine->AddOnScreenDebugMessage(1, 10, FColor::Yellow, *(targetPoint - UnitPawn->GetActorLocation()).ToString());

	GEngine->AddOnScreenDebugMessage(5, 10, FColor::Red, FString::SanitizeFloat(movementDirection.Dot(UnitPawn->GetActorForwardVector())));

	if (FVector::DotProduct(movementDirection, UnitPawn->GetActorForwardVector()) != 1.0f) 
	{
		RotateTo(DeltaTime, FQuat::FindBetween(UnitPawn->GetActorForwardVector(), movementDirection));
		return;
	}

	MoveTo(DeltaTime, targetPoint);
}

void UUnitMovementComponent::RotateTo(float DeltaTime, FQuat Rotation)
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, *Rotation.ToString());
	
	GetOwner()->AddActorLocalRotation(Rotation);


	//GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, FString::SanitizeFloat(Yaw));
	//
	//float currentYaw = GetOwner()->GetActorRotation().Yaw;
	//
	//FQuat rotation(FVector::UpVector, currentYaw - Yaw);
	//
	//GetOwner()->SetActorRotation(rotation);
}

void UUnitMovementComponent::MoveTo(float DeltaTime, FVector Location)
{

}

void UUnitMovementComponent::SetTargetLocation(FVector NewTargetLocation)
{ 
	TargetLocation = NewTargetLocation;
}

void UUnitMovementComponent::UpdatePath()
{
	Path = UNavigationSystemV1::FindPathToLocationSynchronously(UnitPawn, UnitPawn->GetActorLocation(), TargetLocation, UnitPawn);
}

FVector UUnitMovementComponent::GetNextPathPoint()
{
	if (!Path)
	{
		return UnitPawn->GetActorLocation();
	}

	for (FVector point : Path->PathPoints) 
	{
		if (!FVector2D(UnitPawn->GetActorLocation() - point).IsNearlyZero())
			return point;
	}

	return UnitPawn->GetActorLocation();
}