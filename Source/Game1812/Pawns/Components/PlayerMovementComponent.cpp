#include "PlayerMovementComponent.h"

#include "../PlayerPawn.h"
#include "CameraArmComponent.h"
#include "../PlayerCameraSpot.h"

#include <Kismet/GameplayStatics.h>
#include <Camera/CameraComponent.h>


UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MapState = EPlayerCameraState::OutOfMap;

	HalfWidthMapBorder = 100;
	HalfHeightMapBorder = 75;
	Speed = 150;
	Friction = 350;
	Velocity = FVector2D(0);

	LocationInterpSpeed = 15;
	RotationInterpSpeed = 20;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();

	if (owner)
	{
		PlayerPawn = Cast<APlayerPawn>(owner);
	}

	//Find all camera spots in scene

	TArray<AActor*> spotActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCameraSpot::StaticClass(), spotActors);

	TArray<APlayerCameraSpot*> spots;

	for (auto spot : spotActors)
	{
		APlayerCameraSpot* cameraSpot = Cast<APlayerCameraSpot>(spot);

		if (!cameraSpot) continue;

		spots.Add(cameraSpot);
	}

	spots.Sort();

	for (auto spot : spots) 
	{
		CameraSpots.Add(spot);

		if (spot->GetPriority() == 0) CurrentSpot = CameraSpots.Num() - 1;
	}

	if (CameraSpots.Num() != 0) PlayerPawn->GetCameraComponent()->SetWorldTransform(CameraSpots[CurrentSpot]->GetActorTransform());
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MapState != EPlayerCameraState::OutOfMap) 
	{
		if (PlayerPawn->GetPlayerInput()->LookAtMap)
		{
			MapState = EPlayerCameraState::OutOfMap;
			PlayerPawn->GetPlayerInput()->LookAtMap = false;

			PlayerPawn->GetPlayerInput()->MoveLeft = false;
			PlayerPawn->GetPlayerInput()->MoveRight = false;

			Velocity = FVector2D(0);
		}
		else 
		{
			if (MapState == EPlayerCameraState::LookingAtMap) 
			{
				UpdateMovementOnMap(DeltaTime);
			}
			else 
			{
				MoveCameraToMap(DeltaTime);
			}
		}
	}
	else 
	{
		if (PlayerPawn->GetPlayerInput()->LookAtMap)
		{
			MapState = EPlayerCameraState::MovingToMap;
			PlayerPawn->GetPlayerInput()->LookAtMap = false;
		}
		else
		{
			UpdateCameraSpot();

			MoveCameraToCurrentSpot(DeltaTime);
		}
	}
}

void UPlayerMovementComponent::UpdateCameraSpot() 
{
	if (PlayerPawn->GetPlayerInput()->MoveLeft)
	{
		ChangeCameraSpot(-1);

		PlayerPawn->GetPlayerInput()->MoveLeft = false;
	}

	if (PlayerPawn->GetPlayerInput()->MoveRight)
	{
		ChangeCameraSpot(1);

		PlayerPawn->GetPlayerInput()->MoveRight = false;
	}
}

void UPlayerMovementComponent::UpdateMovementOnMap(float deltaTime)
{
	FVector2D inputDirection = GetInputDirection();

	if (inputDirection.IsNearlyZero())
	{
		FVector2D frictionVector = Velocity.GetSafeNormal() * Friction * deltaTime;

		if (Velocity.SizeSquared() > frictionVector.SizeSquared()) 
		{
			Velocity -= frictionVector;
		}
		else 
		{
			Velocity = FVector2D(0);
		}
	}
	else
	{
		Velocity = inputDirection * Speed;
	}

	PlayerPawn->GetCameraArmComponent()->AddRelativeLocation(FVector(Velocity * deltaTime, 0));

	PlayerPawn->GetCameraArmComponent()->AddTargetLength(-PlayerPawn->GetPlayerInput()->MouseScroll * 2.5);

	PlayerPawn->GetPlayerInput()->MouseScroll = 0;

	FVector location = PlayerPawn->GetCameraArmComponent()->GetRelativeLocation();

	PlayerPawn->GetCameraArmComponent()->SetRelativeLocation(FVector(FMath::Clamp(location.X, -HalfHeightMapBorder, HalfHeightMapBorder), FMath::Clamp(location.Y, -HalfWidthMapBorder, HalfWidthMapBorder), location.Z));
}

void UPlayerMovementComponent::MoveCameraToCurrentSpot(float deltaTime) 
{
	APlayerCameraSpot* spot = CameraSpots[CurrentSpot];

	float lip = LocationInterpSpeed;
	float rip = RotationInterpSpeed;

	if (spot->HaveCustomLocationInterpSpeed()) lip = spot->GetLocationInterpSpeed();
	if (spot->HaveCustomRotationInterpSpeed()) rip = spot->GetRotationInterpSpeed();

	FVector moveDelta = FMath::VInterpTo(PlayerPawn->GetCameraComponent()->GetComponentLocation(), spot->GetActorLocation(), deltaTime, lip);
	FRotator rotationDelta = FMath::RInterpTo(PlayerPawn->GetCameraComponent()->GetComponentRotation(), spot->GetActorRotation(), deltaTime, rip);

	PlayerPawn->GetCameraComponent()->SetWorldLocation(moveDelta);
	PlayerPawn->GetCameraComponent()->SetWorldRotation(rotationDelta);
}

void UPlayerMovementComponent::MoveCameraToMap(float deltaTime) 
{
	USceneComponent* cameraPoint = PlayerPawn->GetCameraArmPoint();

	FVector moveDelta = FMath::VInterpTo(PlayerPawn->GetCameraComponent()->GetComponentLocation(), cameraPoint->GetComponentLocation(), deltaTime, LocationInterpSpeed);
	FRotator rotationDelta = FMath::RInterpTo(PlayerPawn->GetCameraComponent()->GetComponentRotation(), cameraPoint->GetComponentRotation(), deltaTime, RotationInterpSpeed);

	PlayerPawn->GetCameraComponent()->SetWorldLocation(moveDelta);
	PlayerPawn->GetCameraComponent()->SetWorldRotation(rotationDelta);

	if ((PlayerPawn->GetCameraComponent()->GetComponentLocation() - cameraPoint->GetComponentLocation()).IsNearlyZero(1) &&
		(PlayerPawn->GetCameraComponent()->GetComponentRotation() - cameraPoint->GetComponentRotation()).IsNearlyZero(0.05))
	{
		MapState = EPlayerCameraState::LookingAtMap;

		PlayerPawn->GetCameraComponent()->SetWorldLocation(cameraPoint->GetComponentLocation());
		PlayerPawn->GetCameraComponent()->SetWorldRotation(cameraPoint->GetComponentRotation());
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

void UPlayerMovementComponent::ChangeCameraSpot(int deltaIndex)
{
	CurrentSpot = FMath::Clamp(CurrentSpot + deltaIndex, 0, CameraSpots.Num() - 1);
}