#include "CossacksGameInstance.h"

#include "Pawns/Unit/Units/AdjutantUnit.h"

#include "Actors/Pieces/ScoutPiece.h"
#include "Actors/Pieces/CombatPiece.h"
#include "Actors/UnitPathArrow.h"

UClass* UCossacksGameInstance::GetCombatUnitPieceClass() const
{
	return CombatUnitPieceClass.Get();
}

UClass* UCossacksGameInstance::GetScoutUnitPieceClass() const
{
	return ScoutUnitPieceClass.Get();
}

UClass* UCossacksGameInstance::GetAdjutantUnitClass() const
{
	return AdjutantUnitClass.Get();
}

UClass* UCossacksGameInstance::GetUnitPathArrowClass() const
{
	return UnitPathArrowClass.Get();
}
