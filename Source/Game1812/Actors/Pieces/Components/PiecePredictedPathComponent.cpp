#include "PiecePredictedPathComponent.h"

#include "../Piece.h"
#include "../ScoutPiece.h"
#include "../../../CossacksGameInstance.h"
#include "../../UnitPathArrow.h"
#include "../../HeadQuarters.h"

UPiecePredictedPathComponent::UPiecePredictedPathComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bIsScout = false;
}

void UPiecePredictedPathComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPiece = Cast<APiece>(GetOwner());

	if (!OwnerPiece)
		return DestroyComponent();

	OwnerPiece->AddOnStartDraggingHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPiecePredictedPathComponent::SpawnArrow));

	OwnerPiece->AddOnMapHitWasDraggedHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPiecePredictedPathComponent::BuildArrow));
	
	OwnerPiece->AddOnOrderAssignHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPiecePredictedPathComponent::DestroyArrow));
	OwnerPiece->AddOnUnitDeathHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPiecePredictedPathComponent::DestroyArrow));

	AHeadQuarters* hq = AHeadQuarters::GetInstance();

	if (hq)
		PathStartPoint = hq->GetActorLocation() + FVector(0.f, 0.f, 100.f);
}

void UPiecePredictedPathComponent::SpawnArrow()
{
	if (OwnerPiece->IsDead())
		return;

	if (UnitPathArrow.IsValid())
		return;

	UCossacksGameInstance* gameInstance = GetWorld()->GetGameInstance<UCossacksGameInstance>();

	if (!gameInstance)
		return;

	UnitPathArrow = GetWorld()->SpawnActor<AUnitPathArrow>(gameInstance->GetUnitPathArrowClass(), FVector::ZeroVector, FRotator::ZeroRotator);

	if (UnitPathArrow.IsValid())
		UnitPathArrow->SetStartPoint(PathStartPoint);
}

void UPiecePredictedPathComponent::BuildArrow()
{
	if (!UnitPathArrow.IsValid())
		return;

	if (bIsScout)
	{
		UnitPathArrow->SetEndPoint(OwnerPiece->GetActorLocation(), false, true);
	}
	else 
	{
		UnitPathArrow->SetEndPoint(OwnerPiece->GetActorLocation(), true);
	}
}

void UPiecePredictedPathComponent::ScoutBuildArrow()
{
	if (!UnitPathArrow.IsValid())
		return;

	UnitPathArrow->SetEndPoint(OwnerPiece->GetActorLocation(), false);
}

void UPiecePredictedPathComponent::DestroyArrow()
{
	UnitPathArrow->Destroy();
	UnitPathArrow = nullptr;

	if (!bIsScout)
		PathStartPoint = OwnerPiece->GetActorLocation();
}

void UPiecePredictedPathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPiecePredictedPathComponent::SetScout(bool NewScout)
{
	bIsScout = NewScout;

	AScoutPiece* scoutPiece = Cast<AScoutPiece>(GetOwner());

	if (!scoutPiece)
		return;

	scoutPiece->AddOnOrderPointAddHandler(FOnPieceChangeDelegate::FDelegate::CreateUObject(this, &UPiecePredictedPathComponent::ScoutBuildArrow));
}

