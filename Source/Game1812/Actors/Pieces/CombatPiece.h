#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "CombatPiece.generated.h"

UCLASS()
class GAME1812_API ACombatPiece : public APiece
{
	GENERATED_BODY()
	
public:

	ACombatPiece();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetComponent* StatsWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCombatUnitDataAsset* CombatUnitData;

	virtual void BeginPlay() override;

	void OnSpawnUnit() override;

	void UpdatePieceMesh();

	void DisplayStatsUI();
	void RemoveStatsUI();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanDisplayStats();

	void OnDeathUnit() override;

	class UCombatUnitDataAsset* GetCombatUnitData() const;
	void SetCombatUnitData(class UCombatUnitDataAsset* NewCombatUnitData);

	virtual void AssignOrder(class UUnitOrder* UnitOrder) override;

	//IDraggable Interface
	void StartCursorHover() override;
	void StopCursorHover() override;
	//
};
