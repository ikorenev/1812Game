#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/Components/Draggable.h"
#include "../Pawns/BaseUnit.h"
#include "../Pawns/CombatUnitEnum.h"
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

	UPROPERTY(EditAnywhere)
	float HoverHeight;

	UPROPERTY(EditAnywhere)
	float SweepCastHeight;

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

	void OnDragStart() override;
	void OnDragEnd() override;

	void OnMouseMove(FVector location, bool hover) override;

	void OnRotate(float yawRotation) override;

	UFUNCTION(BlueprintCallable)
	void AssignOrder(FUnitOrder UnitOrder);
};
