#include "CombatPiece.h"

#include "../Pawns/Unit/CombatUnit.h"
#include "../CossacksGameInstance.h"
#include "HeadQuarters.h"

ACombatPiece::ACombatPiece()
{
}

void ACombatPiece::SpawnUnit()
{
	Super::SpawnUnit();

	ACombatUnit* combatUnit = Cast<ACombatUnit>(Unit);
	
	if (combatUnit)
		combatUnit->SetCombatUnitType(CombatUnitType);
}

void ACombatPiece::SetCombatUnitType(ECombatUnitType NewCombatUnitType)
{
	CombatUnitType = NewCombatUnitType;

	UCossacksGameInstance* gameInstance = GetGameInstance<UCossacksGameInstance>();

	if (!gameInstance)
		return;

	FCombatUnitContainer combatUnitContainer = gameInstance->GetTeamUnitsTable(ETeam::RUSSIA)->FindUnitStatsByType(CombatUnitType);

	PieceFoundationMeshComponent->SetStaticMesh(combatUnitContainer.PieceFoundationMesh);
	PieceFigureMeshComponent->SetStaticMesh(combatUnitContainer.PieceFigureMesh);
}

void ACombatPiece::AssignOrder(FUnitOrder UnitOrder)
{
	Super::AssignOrder(UnitOrder);

	if (AHeadQuarters::GetInstance() && Unit.IsValid())
		AHeadQuarters::GetInstance()->AddOrderToAssign(UnitOrder, Unit.Get());
}
