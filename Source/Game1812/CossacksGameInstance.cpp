#include "CossacksGameInstance.h"

#include "Pawns/Unit/CombatUnitStats.h"
#include "Pawns/Unit/AdjutantUnit.h"

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
