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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCombatUnitDataAsset* CombatUnitData;

	virtual void SpawnUnit() override;

	void UpdatePieceMesh();

public:

	void SetCombatUnitData(class UCombatUnitDataAsset* NewCombatUnitData);

	virtual void AssignOrder(class UUnitOrder* UnitOrder) override;
};
