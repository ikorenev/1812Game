#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/Components/Draggable.h"
#include "Piece.generated.h"

UCLASS()
class GAME1812_API APiece : public AActor, public IDraggable
{
	GENERATED_BODY()
	
public:	

	APiece();

protected:

	FVector TargetLocation;
	bool IsBeingDragged;

	UPROPERTY(EditAnywhere)
	float HoverHeight;

	UPROPERTY(EditAnywhere)
	float SweepCastHeight;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PieceMesh;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void OnDragStart() override;

	void OnDragEnd() override;

	void OnMouseMove(FVector location) override;
};
