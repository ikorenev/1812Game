#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Pawns/Unit/TeamEnum.h"
#include "CossacksGameInstance.generated.h"

UCLASS(BlueprintType)
class GAME1812_API UCossacksGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCombatUnitsTable* RussianUnitsTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCombatUnitsTable* FrenchUnitsTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class APiece> CombatUnitPieceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class APiece> ScoutUnitPieceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AAdjutantUnit> AdjutantUnitClass;


	class UCombatUnitsTable* GetTeamUnitsTable(ETeam Team);
};
