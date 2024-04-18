#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Pawns/Player/Components/Interactable.h"
#include "../../Pawns/Unit/BaseUnit.h"
#include <Blueprint/UserWidget.h>
#include "Piece.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPieceChangeDelegate);

UCLASS()
class GAME1812_API APiece : public AActor, public IInteractable
{
	GENERATED_BODY()

public:

	APiece();

protected:

	//Scene Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* PieceFoundationMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* PieceFigureMeshComponent;

	///

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPieceMapMarkerComponent* MapMarkerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPieceOrderWidgetComponent* OrderWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UPiecePredictedPathComponent* PredictedPathComponent;
	//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class ABaseUnit> Unit;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseUnit> UnitClass;

	UPROPERTY(VisibleAnywhere)
	bool bWasDragged;

	UPROPERTY(VisibleAnywhere)
	bool bCanSpawnUnit;

	UPROPERTY(VisibleAnywhere)
	bool bIsDead;

	FOnPieceChangeDelegate OnUnitSpawn;
	FOnPieceChangeDelegate OnUnitDeath;

	FOnPieceChangeDelegate OnOrderAssign;

	FOnPieceChangeDelegate OnMapHit;
	FOnPieceChangeDelegate OnMapHitWasDragged;

	FOnPieceChangeDelegate OnStartDragging;
	FOnPieceChangeDelegate OnStopDragging;
	FOnPieceChangeDelegate OnStartCursorHover;
	FOnPieceChangeDelegate OnStopCursorHover;
	FOnPieceChangeDelegate OnSelected;
	FOnPieceChangeDelegate OnSelectionRemoved;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SpawnUnit();

	virtual void OnSpawnUnit();

	UFUNCTION(BlueprintNativeEvent)
	void PlaySoundStartDragging();

	UFUNCTION(BlueprintNativeEvent)
	void PlaySoundSelected();

	UFUNCTION(BlueprintNativeEvent)
	void PlaySoundHit(float Force);

	UFUNCTION(BlueprintNativeEvent)
	void PlaySoundDeath();

public:

	virtual void Tick(float DeltaTime) override;

	bool IsDead() const { return bIsDead; }

	//Return true if has related unit and it's not dead
	bool IsPlayed() const { return !bCanSpawnUnit && !bIsDead; }

	UStaticMeshComponent* GetPieceFoundationMeshComponent() const { return PieceFoundationMeshComponent; }
	UStaticMeshComponent* GetPieceFigureMeshComponent() const { return PieceFigureMeshComponent; }

	class ABaseUnit* GetUnit();

	UFUNCTION(BlueprintCallable)
	virtual void AssignOrder(class UUnitOrder* UnitOrder);

	virtual void OnDeathUnit();

	FRotator GetResetRotation();
	void ResetRotation();

	//IDraggable Interface
	virtual void StartDragging() override;
	virtual void StopDragging() override;

	virtual void StartCursorHover() override;
	virtual void StopCursorHover() override;

	virtual void Selected() override;
	virtual void SelectionRemoved() override;

	FVector GetDragOffset() override;
	//

	void AddOnUnitSpawnHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnUnitSpawn.Add(Handler); };
	void AddOnUnitDeathHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnUnitDeath.Add(Handler); };

	void AddOnOrderAssignHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnOrderAssign.Add(Handler); };

	void AddOnMapHitHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnMapHit.Add(Handler); };
	void AddOnMapHitWasDraggedHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnMapHitWasDragged.Add(Handler); };

	void AddOnStartDraggingHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnStartDragging.Add(Handler); };
	void AddOnStopDraggingHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnStopDragging.Add(Handler); };
	void AddOnStartCursorHoverHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnStartCursorHover.Add(Handler); };
	void AddOnStopCursorHoverHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnStopCursorHover.Add(Handler); };
	void AddOnSelectedHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnSelected.Add(Handler); };
	void AddOnSelectionRemovedHandler(const FOnPieceChangeDelegate::FDelegate& Handler) { OnSelectionRemoved.Add(Handler); };
};
