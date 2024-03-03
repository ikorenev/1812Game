#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "../Pawns/Unit/CombatUnitEnum.h"
#include "CombatPiece.generated.h"

UCLASS()
class GAME1812_API ACombatPiece : public APiece
{
	GENERATED_BODY()
	
public:

	ACombatPiece();

protected:

	UPROPERTY(VisibleAnywhere)
	ECombatUnitType CombatUnitType;

	virtual void SpawnUnit() override;

public:

	void SetCombatUnitType(ECombatUnitType NewCombatUnitType);

	virtual void AssignOrder(FUnitOrder UnitOrder) override;
};
