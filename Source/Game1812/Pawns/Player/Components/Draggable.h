#pragma once

#include "Draggable.generated.h"

UINTERFACE()
class GAME1812_API UDraggable : public UInterface
{
    GENERATED_BODY()
};

class GAME1812_API IDraggable
{
    GENERATED_BODY()

public:

    virtual void StartDragging() = 0;

    virtual void StopDragging() = 0;

    virtual void DragToLocation(FVector Location, bool Alt = true) = 0;

    virtual void DragRotate(float YawRotation) = 0;
};
