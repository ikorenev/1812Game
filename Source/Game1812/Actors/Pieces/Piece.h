#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Pawns/Player/Components/Interactable.h"
#include "../../Pawns/Unit/BaseUnit.h"
#include <Blueprint/UserWidget.h>
#include "Piece.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOrderAssignDelegate);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitSpawnDelegate, class ABaseUnit*, NewUnit);

UCLASS()
class GAME1812_API APiece : public AActor, public IInteractable
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
	UMaterialInterface* MaterialOnDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* OrderWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class ABaseUnit> Unit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class APieceMapMarker> MapMarker;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<class AUnitPathArrow> UnitPathArrow;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseUnit> UnitClass;

	UPROPERTY(VisibleAnywhere)
	bool bWasDragged;

	UPROPERTY(VisibleAnywhere)
	bool bCanSpawnUnit;

	UPROPERTY(VisibleAnywhere)
	bool bIsDead;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DisplayOrderUI();
	void RemoveOrderUI();

	void SpawnUnit();
	virtual void CustomUnitSpawn();

	void SpawnMapMarker();
	void SpawnUnitPathArrow();

public:

	FOrderAssignDelegate OnOrderAssign;

	UPROPERTY(BlueprintAssignable)
	FOnUnitSpawnDelegate OnUnitSpawn;

	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void AssignOrder(class UUnitOrder* UnitOrder);

	UStaticMesh* GetPieceFoundationMesh();

	virtual void OnUnitDeath();

	//IDraggable Interface
	virtual void StartDragging() override;
	virtual void StopDragging() override;

	virtual void StartCursorHover() override;
	virtual void StopCursorHover() override;

	virtual void Selected() override;
	virtual void SelectionRemoved() override;

	FVector GetDragOffset() override;
	//

	FRotator GetResetRotation();
	void ResetRotation();


};
