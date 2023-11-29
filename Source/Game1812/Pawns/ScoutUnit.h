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

public:

	virtual void BeginPlay() override;

	void AssignOrder(FUnitOrder NewOrder) override;
};
