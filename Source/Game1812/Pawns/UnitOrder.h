#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UnitOrder.generated.h"

UENUM(BlueprintType)
enum class EUnitEnemyReaction : uint8 {
	ATTACK = 0	UMETA(DisplayName = "DOWN"),
	DEFEND = 1	UMETA(DisplayName = "LEFT"),
};

USTRUCT(BlueprintType)
struct GAME1812_API FUnitOrder
{
	GENERATED_BODY()

public:

	FUnitOrder();

	EUnitEnemyReaction UnitEnemyReaction;

	FVector Location;
	FRotator Rotation;
};
