#include "CossacksGameInstance.h"

#include "Pawns/CombatUnitStats.h"
#include "Pawns/AdjutantUnit.h"

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
