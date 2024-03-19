#include "UnitDeathNotifier.h"

#include "Piece.h"

AUnitDeathNotifier::AUnitDeathNotifier()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AUnitDeathNotifier::SetPiece(APiece* NewPiece)
{
	PieceToNotify = NewPiece;
}

void AUnitDeathNotifier::OnBeingCoveredInFog()
{
	Destroy();
}

void AUnitDeathNotifier::OnBeingRevealedFromFog()
{
	if (PieceToNotify.IsValid())
		//HEAVY IS DEAD
		PieceToNotify->SetUnitDead();

	Destroy();
}

bool AUnitDeathNotifier::IsCoveredInFog()
{
	return true;
}

