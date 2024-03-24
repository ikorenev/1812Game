#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"

UCLASS()
class GAME1812_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPlayerInteractionComponent();

protected:

	class APlayerPawn* PlayerPawn;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionDistance;

	UPROPERTY(EditAnywhere, Category = "Drag and Drop")
	float DraggingHeight;

	UPROPERTY(EditAnywhere, Category = "Drag and Drop")
	float AltDraggingHeight;

	UPROPERTY(EditAnywhere, Category = "Drag and Drop")
	float RotateSpeed;

	class IInteractable* CurrentDraggable;
	class IInteractable* CurrentHovered;
	class IInteractable* CurrentSelected;

	void SetCurrentDraggable(class IInteractable* NewDraggable);
	void SetCurrentHovered(class IInteractable* NewHovered);
	void SetCurrentSelected(class IInteractable* NewSelected);

	virtual void BeginPlay() override;

	FHitResult SingleCursorTrace();
	class IInteractable* FindDraggableAtCursor();

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
