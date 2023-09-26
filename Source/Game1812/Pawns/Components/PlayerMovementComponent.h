#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../PlayerCameraState.h"

#include "PlayerMovementComponent.generated.h"


UCLASS()
class GAME1812_API UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPlayerMovementComponent();

protected:

	class APlayerPawn* PlayerPawn;

	UPROPERTY(VisibleAnywhere)
	EPlayerCameraState CurrentState;

	UPROPERTY(VisibleAnywhere)
	EPlayerCameraState TargetState;

	UPROPERTY(EditAnywhere)
	float HalfWidthMapBorder;

	UPROPERTY(EditAnywhere)
	float HalfHeightMapBorder;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float Friction;

	UPROPERTY(VisibleAnywhere)
	FVector2D Velocity;


	virtual void BeginPlay() override;

	void UpdateTargetState();

	void MoveToTarget(float DeltaTime);

	FVector2D GetInputDirection();

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};