#include "PlayerInteractionComponent.h"

#include "../PlayerPawn.h"
#include "PlayerMovementComponent.h"
#include "Draggable.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentDraggable = nullptr;

	InteractionDistance = 500;
	RotateSpeed = 100;
}

void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!GetOwner())
		return DestroyComponent();

	PlayerPawn = Cast<APlayerPawn>(GetOwner());

	if (!PlayerPawn)
		return DestroyComponent();
}

void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerPawn->GetMovementComponent()->GetMapState() != EPlayerCameraState::LookingAtMap) 
	{
		if (CurrentDraggable)
			SetCurrentDraggable(nullptr);

		return;
	}

	if (CurrentDraggable)
	{
		if (PlayerPawn->GetPlayerInput()->MouseLeftHold && !PlayerPawn->GetMovementComponent()->IsInGlobalMap()) 
		{
			FHitResult hit = SingleCursorTrace();

			CurrentDraggable->OnMouseMove(hit.Location, !PlayerPawn->GetPlayerInput()->MouseRightHold);

			CurrentDraggable->OnRotate((-(float)PlayerPawn->GetPlayerInput()->RotateLeft + (float)PlayerPawn->GetPlayerInput()->RotateRight) * RotateSpeed * DeltaTime);
		}
		else 
		{
			SetCurrentDraggable(nullptr);
		}
	}
	else
	{
		if (PlayerPawn->GetPlayerInput()->MouseLeftClick) 
		{
			PlayerPawn->GetPlayerInput()->MouseLeftClick = false;

			IDraggable* newDraggable = FindDraggableAtCursor();

			if (newDraggable) 
				SetCurrentDraggable(newDraggable);
		}
	}
}

void UPlayerInteractionComponent::SetCurrentDraggable(IDraggable* NewDraggable)
{
	if (CurrentDraggable) 
		CurrentDraggable->OnDragEnd();

	if (NewDraggable)
		NewDraggable->OnDragStart();

	CurrentDraggable = NewDraggable;
}

FHitResult UPlayerInteractionComponent::SingleCursorTrace() 
{
	FVector cursorLocation, cursorDirection;
	PlayerPawn->GetLocalViewingPlayerController()->DeprojectMousePositionToWorld(cursorLocation, cursorDirection);

	FHitResult hit;
	FCollisionQueryParams collisionParams;

	AActor* draggableActor = Cast<AActor>(CurrentDraggable);

	if (draggableActor) 
		collisionParams.AddIgnoredActor(draggableActor);

	GetWorld()->LineTraceSingleByProfile(hit, cursorLocation, cursorLocation + cursorDirection * InteractionDistance, "BlockAll", collisionParams);

	return hit;
}

IDraggable* UPlayerInteractionComponent::FindDraggableAtCursor() 
{
	FHitResult hit = SingleCursorTrace();

	if (!hit.bBlockingHit) 
		return nullptr;

	if (!hit.GetActor()) 
		return nullptr;

	IDraggable* draggable = Cast<IDraggable>(hit.GetActor());

	if (!draggable) 
		return nullptr;

	return draggable;
}