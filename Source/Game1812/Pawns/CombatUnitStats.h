#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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
};

UENUM(BlueprintType)
enum class ECombatUnitType : uint8 {
	TestUnit = 0 UMETA(DisplayName = "Test Unit")
};

USTRUCT(BlueprintType)
struct GAME1812_API FCombatUnitStatsContainer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatUnitType UnitType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCombatUnitStats UnitStats;

};

UCLASS()
class GAME1812_API UCombatUnitsTable : public UDataAsset 
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCombatUnitStatsContainer> Units;
};