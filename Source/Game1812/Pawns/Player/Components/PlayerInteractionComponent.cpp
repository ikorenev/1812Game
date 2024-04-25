#include "PlayerInteractionComponent.h"

#include "../PlayerPawn.h"
#include "PlayerMovementComponent.h"
#include "Interactable.h"

UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CurrentDraggable = nullptr;
	CurrentHovered = nullptr;

	InteractionDistance = 500.f;
	DraggingHeight = 100.f;
	AltDraggingHeight = 10.f;
	RotateSpeed = 100.f;
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
		SetCurrentDraggable(nullptr);
		SetCurrentSelected(nullptr);
		SetCurrentHovered(nullptr);

		return;
	}

	IInteractable* interactable = FindInteractableAtCursor();

	if ((interactable == nullptr) && PlayerPawn->GetPlayerInput()->MouseLeftClick)
	{
		PlayerPawn->GetPlayerInput()->MouseLeftClick = false;

		bIsMultiplySelecting = true;
	}

	if (bIsMultiplySelecting) 
	{
		if (!PlayerPawn->GetPlayerInput()->MouseLeftHold) 
		{
			bIsMultiplySelecting = false;

			FVector cursorStartLocation;
			PlayerPawn->GetLocalViewingPlayerController()->DeprojectMousePositionToWorld(MultipleSelectionStartPoint, cursorStartLocation);
		}
	}


	if (CurrentDraggable)
	{
		if (PlayerPawn->GetPlayerInput()->MouseLeftHold && !PlayerPawn->GetMovementComponent()->IsInGlobalMap()) 
		{
			FHitResult hit = SingleCursorTrace();
			AActor* draggableActor = Cast<AActor>(CurrentDraggable);

			if (!draggableActor)
				return;

			const bool altDragging = PlayerPawn->GetPlayerInput()->MouseRightHold;
			const FVector locationToMoveTo = altDragging ? (hit.Location + FVector(0, 0, AltDraggingHeight)) : (hit.Location + FVector(0, 0, DraggingHeight));
			const FVector newLocation = FMath::VInterpTo(draggableActor->GetActorLocation(), locationToMoveTo, DeltaTime, 20);

			draggableActor->SetActorLocation(newLocation);

			const float rotationDirection = (-(float)PlayerPawn->GetPlayerInput()->RotateLeft + (float)PlayerPawn->GetPlayerInput()->RotateRight);
			const float rotationDelta = rotationDirection * RotateSpeed * DeltaTime;

			draggableActor->AddActorWorldRotation(FRotator(0, rotationDelta, 0));
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

			if (interactable)
				SetCurrentDraggable(interactable);
		}
		else if (PlayerPawn->GetPlayerInput()->MouseRightClick)
		{
			PlayerPawn->GetPlayerInput()->MouseRightClick = false;

			if (CurrentSelected == interactable)
			{
				SetCurrentSelected(nullptr);
			}
			else 
			{
				SetCurrentSelected(interactable);
			}
		}
	}

	if (CurrentHovered != interactable)
		SetCurrentHovered(interactable);
}

void UPlayerInteractionComponent::SetCurrentDraggable(IInteractable* NewDraggable)
{
	if (CurrentDraggable) 
		CurrentDraggable->StopDragging();

	if (NewDraggable)
		NewDraggable->StartDragging();

	CurrentDraggable = NewDraggable;
}

void UPlayerInteractionComponent::SetCurrentHovered(IInteractable* NewHovered)
{
	if (CurrentHovered)
		CurrentHovered->StopCursorHover();

	if (NewHovered)
		NewHovered->StartCursorHover();

	CurrentHovered = NewHovered;
}

void UPlayerInteractionComponent::SetCurrentSelected(IInteractable* NewSelected)
{
	if (CurrentSelected)
		CurrentSelected->SelectionRemoved();

	if (NewSelected)
		NewSelected->Selected();

	CurrentSelected = NewSelected;
}

FHitResult UPlayerInteractionComponent::SingleCursorTrace()
{
	FVector cursorLocation, cursorDirection;
	PlayerPawn->GetLocalViewingPlayerController()->DeprojectMousePositionToWorld(cursorLocation, cursorDirection);

	FHitResult hit;
	FCollisionQueryParams collisionParams;

	collisionParams.bTraceComplex = true;

	AActor* draggableActor = Cast<AActor>(CurrentDraggable);

	if (draggableActor)
		collisionParams.AddIgnoredActor(draggableActor);
	
	GetWorld()->LineTraceSingleByChannel(hit, cursorLocation, cursorLocation + cursorDirection * InteractionDistance, ECC_Visibility, collisionParams);

	return hit;
}

IInteractable* UPlayerInteractionComponent::FindInteractableAtCursor()
{
	FHitResult hit = SingleCursorTrace();

	if (!hit.bBlockingHit) 
		return nullptr;

	if (!hit.GetActor()) 
		return nullptr;

	IInteractable* draggable = Cast<IInteractable>(hit.GetActor());

	if (!draggable) 
		return nullptr;

	return draggable;
}