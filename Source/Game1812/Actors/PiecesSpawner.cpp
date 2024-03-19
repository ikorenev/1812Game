#include "PiecesSpawner.h"

#include "../CossacksGameInstance.h"
#include "Piece.h"

APiecesSpawner::APiecesSpawner()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));

	PieceToSpawn = EPieceToSpawn::COMBAT;
	Team = ETeam::RUSSIA;
	CombatUnitType = ECombatUnitType::NONE;
	SpawnOffset = 40.f;
}

void APiecesSpawner::BeginPlay()
{
	Super::BeginPlay();

	const int SideLength = FMath::CeilToInt(FMath::Sqrt((float)Amount));

	for (int x = 0, i = 0; x < SideLength; x++) 
	{
		for (int y = 0; (y < SideLength) && (i < Amount); y++, i++)
		{
			const FVector SpawnLocation = FVector(x, y, 0) * SpawnOffset;
			const FVector CenterOffset = FVector(1, 1, 0) * SpawnOffset / 2.f;
			const FVector GridOffset = FVector(1, 1, 0) * (SideLength / 2.f) * SpawnOffset;

			SpawnPiece(SpawnLocation + CenterOffset - GridOffset + GetActorLocation());
		}
	}
}

void APiecesSpawner::SpawnPiece(const FVector& Location)
{
	UCossacksGameInstance* gameInstance = GetGameInstance<UCossacksGameInstance>();

	if (!gameInstance)
		return;

	if (PieceToSpawn == EPieceToSpawn::SCOUT)
	{
		GetWorld()->SpawnActor<APiece>(gameInstance->ScoutUnitPieceClass, Location, FRotator::ZeroRotator);
		return;
	}

	APiece* piece = GetWorld()->SpawnActor<APiece>(gameInstance->CombatUnitPieceClass, Location, FRotator::ZeroRotator);

	if (piece)
		piece->SetCombatUnitType(CombatUnitType);
}
