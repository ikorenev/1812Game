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

	class IDraggable* CurrentDraggable;

	UPROPERTY(EditAnywhere)
	float InteractionDistance;

	

	virtual void BeginPlay() override;

	void SetCurrentDraggable(class IDraggable* newDraggable);

	FHitResult SingleCursorTrace();

	class IDraggable* FindDraggableAtCursor();

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
