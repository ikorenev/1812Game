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

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TSet<FIntPoint> ChunksToReveal;

public:

	UPROPERTY(BlueprintAssignable)
	FScoutMovementStateDelegate OnMovementStart;

	UPROPERTY(BlueprintAssignable)
	FScoutMovementStateDelegate OnMovementEnd;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float PredictMovementTime();

	void AssignOrder(FUnitOrder NewOrder) override;
};
