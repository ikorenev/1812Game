#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitOrder.h"
#include "AssignedUnitOrder.generated.h"

USTRUCT(BlueprintType)
struct GAME1812_API FAssignedUnitOrder
{
	GENERATED_BODY()

public:

	FAssignedUnitOrder();
	FAssignedUnitOrder(const FUnitOrder& UnitOrder, class ABaseUnit* Unit);

	~FAssignedUnitOrder();

	UPROPERTY(VisibleAnywhere)
	FUnitOrder UnitOrder;

	UPROPERTY(VisibleAnywhere)
	class ABaseUnit* Unit;

	bool operator==(const FAssignedUnitOrder& Other);
};