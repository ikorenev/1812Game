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
	RotationSpeed = 40;
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

}

void ABaseUnit::AssignOrder(FUnitOrder NewOrder) 
{
	MovementComponent->SetTargetLocation(NewOrder.Location);
	CurrentOrder = NewOrder;
}

float ABaseUnit::GetMovementSpeed() { return MovementSpeed; }
float ABaseUnit::GetRotationSpeed() { return RotationSpeed; }