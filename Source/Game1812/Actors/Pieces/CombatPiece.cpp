#include "CombatPiece.h"

#include "../../Pawns/Unit/Units/CombatUnit.h"
#include "../../DataAssets/CombatUnitDataAsset.h"
#include "../../UI/BaseOrderWidget.h"
#include "../../CossacksGameInstance.h"
#include "../HeadQuarters.h"

#include <Components/BoxComponent.h>
#include <Components/WidgetComponent.h>

ACombatPiece::ACombatPiece()
{
	StatsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("Stats Widget"));
	StatsWidgetComponent->SetRelativeLocation(FVector(0, 0, -100));
	StatsWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	StatsWidgetComponent->SetDrawSize(FVector2D(50, 50));
	StatsWidgetComponent->SetupAttachment(BoxCollisionComponent);
}

void ACombatPiece::BeginPlay()
{
	Super::BeginPlay();

	RemoveStatsUI();

	UBaseOrderWidget* statsWidget = Cast<UBaseOrderWidget>(StatsWidgetComponent->GetWidget());

	if (statsWidget)
		statsWidget->Init(this);
}

void ACombatPiece::OnSpawnUnit()
{
	Super::OnSpawnUnit();

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

void ACombatPiece::DisplayStatsUI()
{
	if (!bIsDead && !bCanSpawnUnit)
		StatsWidgetComponent->SetVisibility(true);
}

void ACombatPiece::RemoveStatsUI()
{
	StatsWidgetComponent->SetVisibility(false);
}

bool ACombatPiece::CanDisplayStats()
{
	if (!Unit.IsValid())
		return false;

	return !Unit->IsCoveredInFog();
}

void ACombatPiece::OnDeathUnit()
{
	Super::OnDeathUnit();

	RemoveStatsUI();
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

void ACombatPiece::StartCursorHover()
{
	DisplayStatsUI();
}

void ACombatPiece::StopCursorHover()
{
	RemoveStatsUI();
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
