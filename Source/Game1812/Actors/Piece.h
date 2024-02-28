#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/Player/Components/Draggable.h"
#include "../Pawns/Unit/BaseUnit.h"
#include "../Pawns/Unit/CombatUnitEnum.h"
#include <Blueprint/UserWidget.h>
#include "Piece.generated.h"

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

	UPROPERTY(EditAnywhere)
	bool bForceOrder;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void RequestOrder();
	void RemoveOrder();

public:

	void SetCombatUnitType(ECombatUnitType NewCombatUnitType);

	virtual void Tick(float DeltaTime) override;

	void StartDragging() override;
	void StopDragging() override;
	FVector GetDragOffset() override;

	UFUNCTION(BlueprintCallable)
	void AssignOrder(FUnitOrder UnitOrder);
};
