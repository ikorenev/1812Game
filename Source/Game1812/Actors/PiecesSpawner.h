#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/TeamEnum.h"
#include "../Pawns/CombatUnitEnum.h"
#include "PiecesSpawner.generated.h"

UENUM()
enum class EPieceToSpawn : uint8 {
	COMBAT = 0	UMETA(DisplayName = "Combat Piece"),
	SCOUT = 1	UMETA(DisplayName = "Scout Piece"),
};



UCLASS()
class GAME1812_API APiecesSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	APiecesSpawner();

protected:

	UPROPERTY(EditAnywhere)
	EPieceToSpawn PieceToSpawn;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "PieceToSpawn==EPieceToSpawn::Combat"))
	ECombatUnitType CombatUnitType;

	UPROPERTY(EditAnywhere)
	ETeam Team;

	UPROPERTY(EditAnywhere)
	int Amount;

	UPROPERTY(EditAnywhere)
	float SpawnOffset;

	virtual void BeginPlay() override;
	
	void SpawnPiece(const FVector& Location);
};
