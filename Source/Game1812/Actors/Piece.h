#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/Player/Components/Draggable.h"
#include "../Pawns/Unit/BaseUnit.h"
#include "../Pawns/Unit/CombatUnitEnum.h"
#include <Blueprint/UserWidget.h>
#include "Piece.generated.h"

DECLARE_MULTICAST_DELEGATE(FMapBordersStartOverlapDelegate);
DECLARE_MULTICAST_DELEGATE(FMapBordersEndOverlapDelegate);
DECLARE_MULTICAST_DELEGATE(FOrderAssignDelegate);

UCLASS()
class GAME1812_API APiece : public AActor, public IDraggable
{
	GENERATED_BODY()

public:

	APiece();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PieceFoundationMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* PieceFigureMeshComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* OrderWidgetComponent;

	UPROPERTY(VisibleAnywhere)
	ECombatUnitType CombatUnitType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseUnit> UnitClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class ABaseUnit* Unit;

	UPROPERTY(VisibleAnywhere)
	bool bWasDragged;

	UPROPERTY(VisibleAnywhere)
	bool bCanSpawnUnit;

	UPROPERTY(EditAnywhere)
	bool bForceOrder;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void RequestOrder();
	void RemoveOrder();

	void SpawnMapMarker();

public:

	FMapBordersStartOverlapDelegate OnMapBordersStartOverlap;
	FMapBordersEndOverlapDelegate OnMapBordersEndOverlap;
	FOrderAssignDelegate OnOrderAssign;

	void SetCombatUnitType(ECombatUnitType NewCombatUnitType);
	UStaticMesh* GetPieceFoundationMesh();

	virtual void Tick(float DeltaTime) override;

	void StartDragging() override;
	void StopDragging() override;
	FVector GetDragOffset() override;

	UFUNCTION(BlueprintCallable)
	void AssignOrder(FUnitOrder UnitOrder);
};
