#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "PlayerCameraState.h"


#include "PlayerPawn.generated.h"

struct FPlayerInput
{
	float MouseScroll;

	bool MoveForward;
	bool MoveBack;
	bool MoveLeft;
	bool MoveRight;

	bool LookAtMap;
};

UCLASS()
class GAME1812_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:

	APlayerPawn();

protected:

	FPlayerInput PlayerInput;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	class UCameraArmComponent* CameraArmComponent;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* CameraArmPoint;

	UPROPERTY(EditAnywhere)
	class UPlayerMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingConfig* InputConfig;


	virtual void BeginPlay() override;

	void MouseScroll(const struct FInputActionValue& Value);
	void MoveForward(const struct FInputActionValue& Value);
	void MoveBack(const struct FInputActionValue& Value);
	void MoveLeft(const struct FInputActionValue& Value);
	void MoveRight(const struct FInputActionValue& Value);
	void LookAtMap(const struct FInputActionValue& Value);

public:

	class UCameraComponent* GetCameraComponent() { return CameraComponent; }

	class UCameraArmComponent* GetCameraArmComponent() { return CameraArmComponent; }

	USceneComponent* GetCameraArmPoint() { return CameraArmPoint; }

	FPlayerInput* GetPlayerInput() { return &PlayerInput; }

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};