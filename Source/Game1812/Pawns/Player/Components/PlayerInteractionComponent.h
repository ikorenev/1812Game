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

	UPROPERTY(EditAnywhere, Category = "Dragging")
	float DraggingHeight;

	UPROPERTY(EditAnywhere, Category = "Dragging")
	float AltDraggingHeight;

	UPROPERTY(EditAnywhere, Category = "Dragging")
	float RotateSpeed;

	UPROPERTY(EditAnywhere, Category = "Selection")
	bool bIsMultiplySelecting;

	UPROPERTY(EditAnywhere, Category = "Selection")
	FVector MultipleSelectionStartPoint;


	class IInteractable* CurrentDraggable;
	class IInteractable* CurrentHovered;
	class IInteractable* CurrentSelected;

	void SetCurrentDraggable(class IInteractable* NewDraggable);
	void SetCurrentHovered(class IInteractable* NewHovered);
	void SetCurrentSelected(class IInteractable* NewSelected);

	virtual void BeginPlay() override;

	FHitResult SingleCursorTrace();
	class IInteractable* FindInteractableAtCursor();

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
