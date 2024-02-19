#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitMovementComponent.generated.h"

DECLARE_DELEGATE(FOnMovementComplete)

UCLASS(Blueprintable, BlueprintType)
class GAME1812_API UUnitMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UUnitMovementComponent();

protected:

	class ABaseUnit* UnitPawn;

	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation;

	UPROPERTY(VisibleAnywhere)
	class UNavigationPath* Path;

	UPROPERTY(VisibleAnywhere)
	bool Moving;

	virtual void BeginPlay() override;

	void UpdateMovement(float DeltaTime);

	void RotateTo(float DeltaTime, float RotationYaw);
	void MoveTo(float DeltaTime, FVector Location);

	FVector GetNextPathPoint();
	FVector GetLastPathPoint();

	void UpdatePath();

	void CheckMovementComplete();

public:	

	FOnMovementComplete OnMovementComplete;

	void SetTargetLocation(FVector NewTargetLocation);

	bool IsMoving() { return Moving; };

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
