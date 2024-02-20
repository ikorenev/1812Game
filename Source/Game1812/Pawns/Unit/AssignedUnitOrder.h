#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssignedUnitOrder.generated.h"

USTRUCT(BlueprintType)
struct GAME1812_API FAssignedUnitOrder
{
	GENERATED_BODY()

protected:

	struct FUnitOrder* UnitOrder;

	class ABaseUnit* Unit;

public:

	FAssignedUnitOrder();
	FAssignedUnitOrder(FUnitOrder UnitOrder, class ABaseUnit* Unit);

	~FAssignedUnitOrder();

	struct FUnitOrder GetUnitOrder() const;
	class ABaseUnit* GetUnit() const;

	bool operator==(const FAssignedUnitOrder& Other);
};