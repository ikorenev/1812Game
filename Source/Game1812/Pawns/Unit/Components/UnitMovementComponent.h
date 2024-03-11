#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementStartDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementEndDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveDelegate, float, Distance);

UCLASS(Blueprintable, BlueprintType)
class GAME1812_API UUnitMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UUnitMovementComponent();

protected:

	class ABaseUnit* UnitPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TargetLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsMoving;

	UPROPERTY()
	class UNavigationPath* Path;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentFollowingSegmentIndex;

	FVector GetNextPathPoint();
	FVector GetLastPathPoint();

	FVector ProjectPointToMap(const FVector& Point);

	virtual void BeginPlay() override;

	void MoveAlongPath(float DeltaTime);

	void UpdateMovement(float DeltaTime);

	void RotatePawn(float DeltaTime, float RotationYaw);
	void MovePawn(float DeltaTime, const FVector& Location);

	void UpdatePath();

	void CheckMovementStart();
	void CheckMovementEnd();

public:	

	FOnMovementStartDelegate OnMovementStart;
	FOnMovementEndDelegate OnMovementEnd;

	FOnMoveDelegate OnMove;

	bool IsMoving();

	void MoveTo(const FVector& MoveToLocation);
	void StopMoving();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
