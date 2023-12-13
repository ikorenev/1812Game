#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "ScoutUnit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FScoutMovementStateDelegate);

UCLASS()
class GAME1812_API AScoutUnit : public ABaseUnit
{
	GENERATED_BODY()

public:

	AScoutUnit();

	TQueue<FVector> ExplorationLocations;

	void OnMovementComplete();

protected:

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;


	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TSet<FIntPoint> ChunksToReveal;

public:

	UPROPERTY(BlueprintAssignable)
	FScoutMovementStateDelegate OnMovementStart;

	UPROPERTY(BlueprintAssignable)
	FScoutMovementStateDelegate OnMovementEnd;


	float GetMovementSpeed() override;
	float GetRotationSpeed() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float PredictMovementTime();

	void AssignOrder(FUnitOrder NewOrder) override;


};
