#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "Components/MoveableUnit.h"
#include "ScoutUnit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoutMovementStateDelegate);

UCLASS()
class GAME1812_API AScoutUnit : public ABaseUnit, public IMoveableUnit
{
	GENERATED_BODY()

public:

	AScoutUnit();

	TQueue<FVector> ExplorationLocations;
	
	UFUNCTION()
	void OnMovementComplete();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUnitMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<FIntPoint> ChunksToReveal;

	UPROPERTY(BlueprintAssignable)
	FScoutMovementStateDelegate OnMovementStart;

	UPROPERTY(BlueprintAssignable)
	FScoutMovementStateDelegate OnMovementEnd;

	virtual void BeginPlay() override;

	void OnOrderAssign(const FUnitOrder& NewOrder) override;

public:

	class UUnitMovementComponent* GetMovementComponent() override;

	float GetMovementSpeed() override;
	float GetRotationSpeed() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float PredictMovementTime();

};
