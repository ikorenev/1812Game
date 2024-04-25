#include "PieceOutlineComponent.h"

#include "../Piece.h"

UPieceOutlineComponent::UPieceOutlineComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsHovered = false;
	bIsBeingDragged = false;
}

void UPieceOutlineComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerPiece = Cast<APiece>(GetOwner());

	if (!OwnerPiece)
		return DestroyComponent();

	OwnerPiece->AddOnStartCursorHoverHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPieceOutlineComponent::OnHoverStart));
	OwnerPiece->AddOnStartDraggingHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPieceOutlineComponent::OnDragStart));
	OwnerPiece->AddOnSelectedHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPieceOutlineComponent::OnSelected));

	OwnerPiece->AddOnStopCursorHoverHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPieceOutlineComponent::OnHoverStop));
	OwnerPiece->AddOnStopDraggingHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPieceOutlineComponent::OnDragStop));
	OwnerPiece->AddOnSelectionRemovedHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPieceOutlineComponent::OnSelectionRemoved));
}

void UPieceOutlineComponent::OnHoverStart()
{
	bIsHovered = true;

	UpdateOutlineState();
}

void UPieceOutlineComponent::OnHoverStop()
{
	bIsHovered = false;

	UpdateOutlineState();
}

void UPieceOutlineComponent::OnDragStart()
{
	bIsBeingDragged = true;

	UpdateOutlineState();
}

void UPieceOutlineComponent::OnDragStop()
{
	bIsBeingDragged = false;

	UpdateOutlineState();
}

void UPieceOutlineComponent::OnSelected()
{
	bIsSelected = true;

	UpdateOutlineState();
}

void UPieceOutlineComponent::OnSelectionRemoved()
{
	bIsSelected = false;

	UpdateOutlineState();
}

void UPieceOutlineComponent::UpdateOutlineState()
{
	SetOutlineEnabled(bIsHovered || bIsBeingDragged || bIsSelected);
}

void UPieceOutlineComponent::SetOutlineEnabled(bool bIsEnabled)
{
	UStaticMeshComponent* meshComponent1 = OwnerPiece->GetPieceFigureMeshComponent();
	UStaticMeshComponent* meshComponent2 = OwnerPiece->GetPieceFoundationMeshComponent();

	if (bIsEnabled) 
	{
		meshComponent1->SetRenderCustomDepth(true);
		meshComponent1->SetCustomDepthStencilValue(2);

		meshComponent2->SetRenderCustomDepth(true);
		meshComponent2->SetCustomDepthStencilValue(2);
		return;
	}

	meshComponent1->SetRenderCustomDepth(false);
	meshComponent1->SetCustomDepthStencilValue(0);

	meshComponent2->SetRenderCustomDepth(false);
	meshComponent2->SetCustomDepthStencilValue(0);
}
