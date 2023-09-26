#include "CameraArmComponent.h"

#include "../PlayerPawn.h"

UCameraArmComponent::UCameraArmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;



	CurrentLength = 200;
}

void UCameraArmComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetLength = CurrentLength;
	MaxLength = 400;
	MinLength = 10;

	if (!GetOwner()) return;

	PlayerPawn = Cast<APlayerPawn>(GetOwner());

	if (!PlayerPawn) return;

	PlayerPawn->GetCameraArmPoint()->SetRelativeLocation(FVector(-CurrentLength, 0, 0));
}


void UCameraArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



}

