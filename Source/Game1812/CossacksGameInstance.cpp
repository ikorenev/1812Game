#include "CossacksGameInstance.h"

#include "Pawns/Unit/Units/AdjutantUnit.h"

<<<<<<< Updated upstream
#include "Actors/Pieces/ScoutPiece.h"
#include "Actors/Pieces/CombatPiece.h"
#include "Actors/UnitPathArrow.h"
#include "Actors/GhostPiece.h"

UClass* UCossacksGameInstance::GetCombatUnitPieceClass() const
=======
UCombatUnitsTable* UCossacksGameInstance::GetTeamUnitsTable(ETeam Team)
>>>>>>> Stashed changes
{
	return CombatUnitPieceClass.Get();
}
<<<<<<< Updated upstream

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

UClass* UCossacksGameInstance::GetGhostPieceClass() const
{
	return GhostPieceClass.Get();
}
=======
>>>>>>> Stashed changes
