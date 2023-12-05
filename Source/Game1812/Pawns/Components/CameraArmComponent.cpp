#include "CameraArmComponent.h"

#include "../PlayerPawn.h"

UCameraArmComponent::UCameraArmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	

	MaxLength = 400;
	MinLength = 20;
}

void UCameraArmComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentLength = MaxLength;
	TargetLength = CurrentLength;


	if (!GetOwner()) return;

	PlayerPawn = Cast<APlayerPawn>(GetOwner());

	if (!PlayerPawn) return;
}


void UCameraArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentLength = FMath::FInterpTo(CurrentLength, TargetLength, DeltaTime, 5);

	PlayerPawn->GetCameraArmPoint()->SetRelativeLocation(FVector(-CurrentLength, 0, 0));
}

