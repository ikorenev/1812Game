#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pawns/Unit/TeamEnum.h"
#include "CossacksGameInstance.generated.h"

UCLASS(BlueprintType)
class GAME1812_API UCossacksGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ACombatPiece> CombatUnitPieceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AScoutPiece> ScoutUnitPieceClass;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCombatUnitsTable* RussianUnitsTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCombatUnitsTable* FrenchUnitsTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AAdjutantUnit> AdjutantUnitClass;
	
	UClass* GetCombatUnitPieceClass();
	UClass* GetScoutUnitPieceClass();

	class UCombatUnitsTable* GetTeamUnitsTable(ETeam Team);
};
