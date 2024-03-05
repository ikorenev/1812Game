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
	class IMoveableUnit* MoveableUnit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsMoving;

	UPROPERTY()
	class UNavigationPath* Path;

	virtual void BeginPlay() override;

	void MoveAlongPath(float DeltaTime);

	void UpdateMovement(float DeltaTime);

	void RotateTo(float DeltaTime, float RotationYaw);
	void MoveTo(float DeltaTime, FVector Location);

	FVector GetNextPathPoint();
	FVector GetLastPathPoint();

	void UpdatePath();

	void CheckMovementComplete();

public:	

	FOnMovementComplete OnMovementComplete;

	bool IsMoving();

	void SetTargetLocation(FVector NewTargetLocation);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	///void MoveTo(const FVector& MoveToLocation);
};
