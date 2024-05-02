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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AAdjutantUnit> AdjutantUnitClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AUnitPathArrow> UnitPathArrowClass;

<<<<<<< Updated upstream
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AGhostPiece> GhostPieceClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* PieceMapMarkerMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* DeadPieceMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMaterialInterface* CombatStatsPieceMaterial;

public:

	UClass* GetCombatUnitPieceClass() const;
	UClass* GetScoutUnitPieceClass() const;

	UClass* GetAdjutantUnitClass() const;

	UClass* GetUnitPathArrowClass() const;
	UClass* GetGhostPieceClass() const;

	UMaterialInterface* GetPieceMapMarkerMaterial() const { return PieceMapMarkerMaterial; }
	UMaterialInterface* GetDeadPieceMaterial() const { return DeadPieceMaterial; };
	UMaterialInterface* GetCombatStatsPieceMaterial() const { return CombatStatsPieceMaterial; };
	
=======
	class UCombatUnitsTable* GetTeamUnitsTable(ETeam Team);
>>>>>>> Stashed changes
};
