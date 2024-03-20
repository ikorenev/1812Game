#include "CombatPiece.h"

#include "../Pawns/Unit/CombatUnit.h"
#include "../Pawns/Unit/CombatUnitDataAsset.h"
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
		combatUnit->SetCombatUnitData(CombatUnitData);
}

void ACombatPiece::UpdatePieceMesh()
{
	if (!CombatUnitData)
		return;

	PieceFoundationMeshComponent->SetStaticMesh(CombatUnitData->GetPieceFoundationMesh());
	PieceFigureMeshComponent->SetStaticMesh(CombatUnitData->GetPieceMesh());
}

void ACombatPiece::AssignOrder(UUnitOrder* UnitOrder)
{
	Super::AssignOrder(UnitOrder);

	UCombatUnitOrder* combatUnitOrder = Cast<UCombatUnitOrder>(UnitOrder);

	if (!combatUnitOrder)
		return;

	if (AHeadQuarters::GetInstance() && Unit.IsValid())
		AHeadQuarters::GetInstance()->AddOrderToAssign(combatUnitOrder, Unit.Get());
}

UCombatUnitDataAsset* ACombatPiece::GetCombatUnitData() const
{
	return CombatUnitData;
}

void ACombatPiece::SetCombatUnitData(UCombatUnitDataAsset* NewCombatUnitData)
{
	CombatUnitData = NewCombatUnitData;

	UpdatePieceMesh();
}
