#include "CossacksGameInstance.h"

#include "Pawns/CombatUnitStats.h"
#include "Pawns/AdjutantUnit.h"

<<<<<<< Updated upstream
UCombatUnitsTable* UCossacksGameInstance::GetTeamUnitsTable(ETeam Team)
=======
#include "Actors/Pieces/ScoutPiece.h"
#include "Actors/Pieces/CombatPiece.h"
#include "Actors/UnitPathArrow.h"
#include "Actors/GhostPiece.h"
#include "Actors/EnemyPiece.h"

UClass* UCossacksGameInstance::GetCombatUnitPieceClass() const
>>>>>>> Stashed changes
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

UClass* UCossacksGameInstance::GetEnemyPieceClass() const
{
	return EnemyPieceClass.Get();
}
