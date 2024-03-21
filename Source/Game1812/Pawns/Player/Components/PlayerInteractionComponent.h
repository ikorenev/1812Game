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

	class IDraggable* CurrentDraggable;
	class IDraggable* CurrentHovered;
	class IDraggable* CurrentSelected;

	void SetCurrentDraggable(class IDraggable* NewDraggable);
	void SetCurrentHovered(class IDraggable* NewHovered);
	void SetCurrentSelected(class IDraggable* NewSelected);

	virtual void BeginPlay() override;

	FHitResult SingleCursorTrace();
	class IDraggable* FindDraggableAtCursor();

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
