#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CombatUnitEnum.h"
#include "CombatUnitStats.generated.h"


USTRUCT(BlueprintType)
struct GAME1812_API FCombatUnitStats
{
	GENERATED_USTRUCT_BODY()
	
public:

	FCombatUnitStats();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyDetectionRange;
};

USTRUCT(BlueprintType)
struct GAME1812_API FCombatUnitContainer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatUnitType UnitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* PieceFigureMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* PieceFoundationMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCombatUnitStats UnitStats;

};

UCLASS()
class GAME1812_API UCombatUnitsTable : public UDataAsset 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCombatUnitContainer> Units;

	FCombatUnitContainer FindUnitStatsByType(ECombatUnitType CombatUnitType);
};