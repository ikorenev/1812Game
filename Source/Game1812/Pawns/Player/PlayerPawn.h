#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PlayerCameraStateEnum.h"

#include "PlayerPawn.generated.h"

struct FPlayerInput
{
public:

	FPlayerInput();

	float MouseScroll;

	bool MoveForward;
	bool MoveBack;
	bool MoveLeft;
	bool MoveRight;

	bool LookAtMap;

	bool MouseLeftClick;
	bool MouseLeftHold;

	bool MouseRightClick;
	bool MouseRightHold;

	bool RotateLeft;
	bool RotateRight;
};

UCLASS()
class GAME1812_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:

	APlayerPawn();

protected:

	FPlayerInput PlayerInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingConfig* InputConfig;

	//Components

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraArmComponent* CameraArmComponent;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* CameraArmPoint;

	UPROPERTY(VisibleAnywhere)
	class UPlayerMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	class UPlayerInteractionComponent* InteractionComponent;

	virtual void BeginPlay() override;

	void MouseScroll(const struct FInputActionValue& Value);
	void MouseLeftClick(const struct FInputActionValue& Value);
	void MouseRightClick(const struct FInputActionValue& Value);
	void MoveForward(const struct FInputActionValue& Value);
	void MoveBack(const struct FInputActionValue& Value);
	void MoveLeft(const struct FInputActionValue& Value);
	void MoveRight(const struct FInputActionValue& Value);
	void LookAtMap(const struct FInputActionValue& Value);
	void RotateLeft(const struct FInputActionValue& Value);
	void RotateRight(const struct FInputActionValue& Value);

public:

	class UCameraComponent* GetCameraComponent() { return CameraComponent; }
	class UCameraArmComponent* GetCameraArmComponent() { return CameraArmComponent; }
	class UPlayerMovementComponent* GetMovementComponent() { return MovementComponent; }
	USceneComponent* GetCameraArmPoint() { return CameraArmPoint; }

	FPlayerInput* GetPlayerInput() { return &PlayerInput; }

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};