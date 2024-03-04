#include "CossacksGameInstance.h"

#include "Pawns/Unit/CombatUnitStats.h"
#include "Pawns/Unit/AdjutantUnit.h"

#include "Actors/ScoutPiece.h"
#include "Actors/CombatPiece.h"

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

UCombatUnitsTable* UCossacksGameInstance::GetTeamUnitsTable(ETeam Team)
{
	switch (Team)
	{
	case ETeam::RUSSIA:
		return RussianUnitsTable;
	case ETeam::FRANCE:
		return FrenchUnitsTable;
	}

	return nullptr;
}
