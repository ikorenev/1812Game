#pragma once

#include "CoreMinimal.h"
#include "CombatUnitType.generated.h"

UENUM()
enum class ECombatUnitType : uint8
{
	Infantry	UMETA(DisplayName = "Infantry"),
	Cavalry		UMETA(DisplayName = "Cavalry"),
	Artillery	UMETA(DisplayName = "Artillery")
};

