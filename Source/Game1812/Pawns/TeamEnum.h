#pragma once

#include "CoreMinimal.h"
#include "TeamEnum.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8 {
	RUSSIA = 0	UMETA(DisplayName = "Russian Empire"),
	FRANCE = 1	UMETA(DisplayName = "French Empire"),
};

