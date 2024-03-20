#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "ScoutPiece.generated.h"

UCLASS()
class GAME1812_API AScoutPiece : public APiece
{
	GENERATED_BODY()
	
public:

	AScoutPiece();

protected:

public:

	virtual void AssignOrder(class UUnitOrder* UnitOrder) override;
};
