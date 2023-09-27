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

    virtual void OnDragStart() {}

    virtual void OnDragEnd() {}

    virtual void OnMouseMove(FVector location) {}
};
