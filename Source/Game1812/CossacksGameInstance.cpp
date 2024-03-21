#include "CossacksGameInstance.h"

#include "Pawns/Unit/AdjutantUnit.h"

#include "Actors/ScoutPiece.h"
#include "Actors/CombatPiece.h"
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
