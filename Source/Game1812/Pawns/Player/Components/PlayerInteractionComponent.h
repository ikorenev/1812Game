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

	void SetCurrentDraggable(class IDraggable* NewDraggable);

	virtual void BeginPlay() override;

	FHitResult SingleCursorTrace();
	class IDraggable* FindDraggableAtCursor();

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};