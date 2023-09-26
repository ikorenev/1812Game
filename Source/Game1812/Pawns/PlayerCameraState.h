#pragma once

#include "CoreMinimal.h"
#include "PlayerCameraState.generated.h"

UENUM(BlueprintType)
enum class EPlayerCameraState : uint8
{
	Default = 0,
	LookingAtMap = 1,
	LookingLeft = 2,
	LookingRight = 3
};