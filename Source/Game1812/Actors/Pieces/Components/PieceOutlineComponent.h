#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PieceOutlineComponent.generated.h"

UCLASS()
class GAME1812_API UPieceOutlineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPieceOutlineComponent();

protected:

	class APiece* OwnerPiece;

	bool bIsHovered;
	bool bIsBeingDragged;
	bool bIsSelected;

	virtual void BeginPlay() override;

	void OnHoverStart();
	void OnHoverStop();

	void OnDragStart();
	void OnDragStop();

	void OnSelected();
	void OnSelectionRemoved();

	void UpdateOutlineState();

	void SetOutlineEnabled(bool bIsEnabled);

public:	
		
};
