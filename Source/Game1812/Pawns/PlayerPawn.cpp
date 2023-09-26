#include "PlayerPawn.h"

#include <Camera/CameraComponent.h>
#include <Components/ArrowComponent.h>

#include "Components/PlayerMovementComponent.h"
#include "Components/CameraArmComponent.h"
#include "../Configs/InputMappingConfig.h"

#include "EnhancedInput/Public/InputActionValue.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"

#include "EnhancedInput/Public/EnhancedInputSubsystems.h"


APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

	CameraArmComponent = CreateDefaultSubobject<UCameraArmComponent>(TEXT("Camera Arm"));
	CameraArmComponent->SetupAttachment(RootComponent);

	CameraArmPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Point"));
	CameraArmPoint->SetupAttachment(CameraArmComponent);


	TTuple<EPlayerCameraState, FName> arrows[3] = {
		MakeTuple(EPlayerCameraState::Default, "Default Spot"),
		MakeTuple(EPlayerCameraState::LookingLeft, "Left Spot"),
		MakeTuple(EPlayerCameraState::LookingRight, "Right Spot")
	};

	for (auto arrow : arrows)
	{
		UArrowComponent* arrowComponent = CreateDefaultSubobject<UArrowComponent>(arrow.Get<1>());
		arrowComponent->SetupAttachment(RootComponent);
		CameraSpots.Add(arrow.Get<0>(), arrowComponent);
	}

	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement Component"));
}

void APlayerPawn::MoveForward(const FInputActionValue& Value) { PlayerInput.MoveForward = Value.Get<bool>(); };
void APlayerPawn::MoveBack(const FInputActionValue& Value) { PlayerInput.MoveBack = Value.Get<bool>(); };
void APlayerPawn::MoveLeft(const FInputActionValue& Value) { PlayerInput.MoveLeft = Value.Get<bool>(); };
void APlayerPawn::MoveRight(const FInputActionValue& Value) { PlayerInput.MoveRight = Value.Get<bool>(); };
void APlayerPawn::LookAtMap(const FInputActionValue& Value) { PlayerInput.LookAtMap = Value.Get<bool>(); };

FTransform APlayerPawn::GetCameraSpot(EPlayerCameraState state)
{
	return CameraSpots.Contains(state) ? CameraSpots[state]->GetComponentTransform() : FTransform();
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!InputConfig) return;

	APlayerController* playerController = Cast<APlayerController>(GetController());

	if (!playerController) return;

	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());

	if (!subsystem) return;

	subsystem->ClearAllMappings();
	subsystem->AddMappingContext(InputMapping, 0);


	UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PlayerEnhancedInputComponent->BindAction(InputConfig->MoveForward, ETriggerEvent::Triggered, this, &APlayerPawn::MoveForward);
	PlayerEnhancedInputComponent->BindAction(InputConfig->MoveBack, ETriggerEvent::Triggered, this, &APlayerPawn::MoveBack);
	PlayerEnhancedInputComponent->BindAction(InputConfig->MoveLeft, ETriggerEvent::Triggered, this, &APlayerPawn::MoveLeft);
	PlayerEnhancedInputComponent->BindAction(InputConfig->MoveRight, ETriggerEvent::Triggered, this, &APlayerPawn::MoveRight);

	PlayerEnhancedInputComponent->BindAction(InputConfig->LookAtMap, ETriggerEvent::Triggered, this, &APlayerPawn::LookAtMap);
}