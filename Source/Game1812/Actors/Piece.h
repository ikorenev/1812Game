#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/Player/Components/Draggable.h"
#include "../Pawns/Unit/BaseUnit.h"

#include <Blueprint/UserWidget.h>
#include "Piece.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOrderAssignDelegate);

UCLASS()
class GAME1812_API APiece : public AActor, public IDraggable
{
	GENERATED_BODY()

public:

	APiece();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* PieceFoundationMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* PieceFigureMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* OrderWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class ABaseUnit> Unit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class APieceMapMarker> MapMarker;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseUnit> UnitClass;

	UPROPERTY(VisibleAnywhere)
	bool bWasDragged;

	UPROPERTY(VisibleAnywhere)
	bool bCanSpawnUnit;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void RequestOrder();
	void RemoveOrder();

	virtual void SpawnUnit();
	virtual void SpawnMapMarker();

public:

	FOrderAssignDelegate OnOrderAssign;
	
	UStaticMesh* GetPieceFoundationMesh();

	virtual void Tick(float DeltaTime) override;

	void StartDragging() override;
	void StopDragging() override;
	FVector GetDragOffset() override;

	FRotator GetResetRotation();
	void ResetRotation();

	UFUNCTION(BlueprintCallable)
	virtual void AssignOrder(FUnitOrder UnitOrder);
};
