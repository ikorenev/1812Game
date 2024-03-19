#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MoveableUnit.generated.h"

UINTERFACE()
class GAME1812_API UMoveableUnit : public UInterface
{
    GENERATED_BODY()
};

class GAME1812_API IMoveableUnit
{
    GENERATED_BODY()

public:

    virtual class UUnitMovementComponent* GetMovementComponent() = 0;

    virtual float GetMovementSpeed() = 0;
    virtual float GetRotationSpeed() = 0;
};