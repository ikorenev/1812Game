#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitOrder.h"
#include "OrderAndUnitContainer.generated.h"

USTRUCT(BlueprintType)
struct GAME1812_API FOrderAndUnitContainer
{
	GENERATED_BODY()

public:

	FOrderAndUnitContainer();
	FOrderAndUnitContainer(const FUnitOrder& UnitOrder, class ABaseUnit* Unit);

	~FOrderAndUnitContainer();

	UPROPERTY(VisibleAnywhere)
	FUnitOrder UnitOrder;

	UPROPERTY(VisibleAnywhere)
	class ABaseUnit* Unit;

	bool operator==(const FOrderAndUnitContainer& Other);
};