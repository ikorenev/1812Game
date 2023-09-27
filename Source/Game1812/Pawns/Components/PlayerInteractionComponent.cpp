#include "PlayerInteractionComponent.h"

#include "../PlayerPawn.h"
#include "PlayerMovementComponent.h"
#include "Draggable.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	InteractionDistance = 500;
	CurrentDraggable = nullptr;
}

void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* owner = GetOwner();

	if (owner)
	{
		PlayerPawn = Cast<APlayerPawn>(owner);
	}
	
}

void UPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerPawn->GetMovementComponent()->GetMapState() == EPlayerCameraState::LookingAtMap) 
	{
		if (CurrentDraggable)
		{
			if (PlayerPawn->GetPlayerInput()->MouseLeftHold) 
			{
				FHitResult hit = SingleCursorTrace();

				CurrentDraggable->OnMouseMove(hit.Location);
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

				if (newDraggable) SetCurrentDraggable(newDraggable);
			}
		}
	}

	
}

void UPlayerInteractionComponent::SetCurrentDraggable(IDraggable* newDraggable)
{
	if (CurrentDraggable) CurrentDraggable->OnDragEnd();

	if (newDraggable) newDraggable->OnDragStart();

	CurrentDraggable = newDraggable;
}

FHitResult UPlayerInteractionComponent::SingleCursorTrace() 
{
	FVector cursorLocation, cursorDirection;

	PlayerPawn->GetLocalViewingPlayerController()->DeprojectMousePositionToWorld(cursorLocation, cursorDirection);

	FHitResult hit;

	FCollisionQueryParams collisionParams;

	AActor* draggableActor = Cast<AActor>(CurrentDraggable);

	if (draggableActor) collisionParams.AddIgnoredActor(draggableActor);

	GetWorld()->LineTraceSingleByProfile(hit, cursorLocation, cursorLocation + cursorDirection * InteractionDistance, "BlockAll", collisionParams);

	return hit;
}

IDraggable* UPlayerInteractionComponent::FindDraggableAtCursor() 
{
	FHitResult hit = SingleCursorTrace();

	if (!hit.bBlockingHit) return nullptr;

	if (!hit.GetActor()) return nullptr;

	IDraggable* draggable = Cast<IDraggable>(hit.GetActor());

	if (!draggable) return nullptr;

	return draggable;
}