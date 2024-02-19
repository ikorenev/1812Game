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

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float RotateSpeed;

	class IDraggable* CurrentDraggable;

	void SetCurrentDraggable(class IDraggable* NewDraggable);

	virtual void BeginPlay() override;

	FHitResult SingleCursorTrace();
	class IDraggable* FindDraggableAtCursor();

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
