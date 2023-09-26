#include "PlayerMovementComponent.h"

#include "../PlayerPawn.h"
#include "CameraArmComponent.h"

#include <Camera/CameraComponent.h>


UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentState = EPlayerCameraState::Default;
	TargetState = EPlayerCameraState::Default;

	HalfWidthMapBorder = 100;
	HalfHeightMapBorder = 75;
	Speed = 150;
	Friction = 350;
	Velocity = FVector2D(0);
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();

	if (owner)
	{
		PlayerPawn = Cast<APlayerPawn>(owner);
	}

	PlayerPawn->GetCameraComponent()->SetWorldTransform(PlayerPawn->GetCameraSpot(EPlayerCameraState::Default));
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentState == TargetState) UpdateTargetState();

	if (CurrentState != TargetState)
	{
		MoveToTarget(DeltaTime);
	}
	else
	{
		if (CurrentState == EPlayerCameraState::LookingAtMap)
		{
			FVector2D inputDirection = GetInputDirection();

			if (inputDirection.IsNearlyZero())
			{
				Velocity -= Velocity.GetSafeNormal() * Friction * DeltaTime;
			}
			else
			{
				Velocity = inputDirection * Speed;
			}

			PlayerPawn->GetCameraArmComponent()->AddRelativeLocation(FVector(Velocity * DeltaTime, 0));
		}
	}

}

void UPlayerMovementComponent::UpdateTargetState()
{
	if (CurrentState == EPlayerCameraState::LookingAtMap)
	{
		if (PlayerPawn->GetPlayerInput()->LookAtMap)
		{
			TargetState = EPlayerCameraState::Default;

			PlayerPawn->GetPlayerInput()->LookAtMap = false;
		}
	}
	else
	{
		if (PlayerPawn->GetPlayerInput()->LookAtMap)
		{
			TargetState = EPlayerCameraState::LookingAtMap;

			PlayerPawn->GetPlayerInput()->LookAtMap = false;
		}

		if (PlayerPawn->GetPlayerInput()->MoveLeft)
		{
			TargetState = EPlayerCameraState::LookingLeft;

			PlayerPawn->GetPlayerInput()->MoveLeft = false;
		}

		if (PlayerPawn->GetPlayerInput()->MoveRight)
		{
			TargetState = EPlayerCameraState::LookingRight;

			PlayerPawn->GetPlayerInput()->MoveRight = false;
		}

		if (PlayerPawn->GetPlayerInput()->MoveBack)
		{
			TargetState = EPlayerCameraState::Default;

			PlayerPawn->GetPlayerInput()->MoveBack = false;
		}
	}
}

void UPlayerMovementComponent::MoveToTarget(float DeltaTime)
{
	FTransform spot;

	if (TargetState == EPlayerCameraState::LookingAtMap)
	{
		spot = PlayerPawn->GetCameraArmPoint()->GetComponentTransform();
	}
	else
	{
		spot = PlayerPawn->GetCameraSpot(TargetState);
	}

	FVector moveDelta = FMath::VInterpTo(PlayerPawn->GetCameraComponent()->GetComponentLocation(), spot.GetLocation(), DeltaTime, 15);
	FRotator rotationDelta = FMath::RInterpTo(PlayerPawn->GetCameraComponent()->GetComponentRotation(), spot.GetRotation().Rotator(), DeltaTime, 20);

	PlayerPawn->GetCameraComponent()->SetWorldLocation(moveDelta);
	PlayerPawn->GetCameraComponent()->SetWorldRotation(rotationDelta);

	if ((PlayerPawn->GetCameraComponent()->GetComponentLocation() - spot.GetLocation()).IsNearlyZero(1) &&
		(PlayerPawn->GetCameraComponent()->GetComponentRotation() - spot.GetRotation().Rotator()).IsNearlyZero(0.05))
	{
		CurrentState = TargetState;

		PlayerPawn->GetCameraComponent()->SetWorldLocation(spot.GetLocation());
		PlayerPawn->GetCameraComponent()->SetWorldRotation(spot.GetRotation().Rotator());

		if (CurrentState == EPlayerCameraState::LookingAtMap)
		{
			PlayerPawn->GetCameraComponent()->AttachToComponent(PlayerPawn->GetCameraArmPoint(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

FVector2D UPlayerMovementComponent::GetInputDirection()
{
	FVector direction(0);

	if (PlayerPawn->GetPlayerInput()->MoveForward) direction += PlayerPawn->GetActorForwardVector();
	if (PlayerPawn->GetPlayerInput()->MoveBack) direction -= PlayerPawn->GetActorForwardVector();
	if (PlayerPawn->GetPlayerInput()->MoveRight) direction += PlayerPawn->GetActorRightVector();
	if (PlayerPawn->GetPlayerInput()->MoveLeft) direction -= PlayerPawn->GetActorRightVector();

	return FVector2D(direction).GetSafeNormal();
}