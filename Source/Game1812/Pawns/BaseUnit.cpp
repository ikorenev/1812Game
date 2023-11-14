#include "BaseUnit.h"

#include <Components/BoxComponent.h>

#include "Components/UnitMovementComponent.h"

ABaseUnit::ABaseUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	BoxComponent->InitBoxExtent(FVector(10, 10, 5));
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RootComponent = BoxComponent;

	MovementComponent = CreateDefaultSubobject<UUnitMovementComponent>(FName("Movement Component"));

	MovementSpeed = 10;
}

void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	AddActorWorldOffset(FVector(0, 0, 10));

	AddActorWorldOffset(FVector(0, 0, -20), true);
}

void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	return;
	FRotator targetRotation = FRotator(0);

	if (!((GetActorLocation() - TargetLocation) * FVector(1, 1, 0)).IsNearlyZero(5))
	{
		FVector delta = (TargetLocation - GetActorLocation()) * FVector(1, 1, 0);

		FVector direction = delta.GetSafeNormal();

		FVector distance = direction * MovementSpeed * DeltaTime;

		if (distance.SizeSquared() > delta.SizeSquared()) 
		{
			SetActorLocation(TargetLocation);
		}
		else 
		{
			AddActorWorldOffset(distance);
		}

		AddActorWorldOffset(FVector(0, 0, 10));

		AddActorWorldOffset(FVector(0, 0, -20), true);

		targetRotation = FRotator(0, FMath::RadiansToDegrees(direction.Y > 0 ? FMath::Atan(-direction.X / direction.Y) : FMath::Atan(-direction.X / direction.Y) + PI), 0);
	}
	
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), targetRotation, DeltaTime, 20));
}

void ABaseUnit::MoveToLocation(FVector location)
{
	MovementComponent->SetTargetLocation(location);
}