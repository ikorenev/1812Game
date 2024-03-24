#include "CossacksGameInstance.h"

#include "Pawns/Unit/Units/AdjutantUnit.h"

#include "Actors/Pieces/ScoutPiece.h"
#include "Actors/Pieces/CombatPiece.h"
#include "Actors/UnitPathArrow.h"

UClass* UCossacksGameInstance::GetCombatUnitPieceClass()
{
	return CombatUnitPieceClass.Get();
}

UClass* UCossacksGameInstance::GetScoutUnitPieceClass()
{
	return ScoutUnitPieceClass.Get();
}

UMaterial* UCossacksGameInstance::GetPieceMapMarkerMaterial()
{
	return PieceMapMarkerMaterial;
}

TSubclassOf<class AUnitPathArrow> UCossacksGameInstance::GetUnitPathArrowClass()
{
	return UnitPathArrowClass;
}
