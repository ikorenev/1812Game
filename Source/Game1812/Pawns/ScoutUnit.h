#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "ScoutUnit.generated.h"

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

	virtual void Tick(float DeltaTime) override;

	void AssignOrder(FUnitOrder NewOrder) override;
};
