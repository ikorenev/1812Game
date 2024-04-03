#pragma once

#include "Interactable.generated.h"

UINTERFACE()
class GAME1812_API UInteractable : public UInterface
{
    GENERATED_BODY()
};

class GAME1812_API IInteractable
{
    GENERATED_BODY()

public:

    virtual void StartDragging() = 0;
    virtual void StopDragging() = 0;

    virtual void StartCursorHover() = 0;
    virtual void StopCursorHover() = 0;

    virtual void Selected() = 0;
    virtual void SelectionRemoved() = 0;

    virtual FVector GetDragOffset() = 0;
};
