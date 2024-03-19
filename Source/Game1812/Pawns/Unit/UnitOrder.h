#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssignedUnitOrder.h"
#include "UnitOrder.generated.h"

UENUM(BlueprintType)
enum class EUnitEnemyReaction : uint8 {
	ATTACK = 0	UMETA(DisplayName = "ATTACK"),
	DEFEND = 1	UMETA(DisplayName = "DEFEND"),
};

USTRUCT(BlueprintType)
struct GAME1812_API FUnitOrder
{
	GENERATED_BODY()

public:
	
	FUnitOrder();
	FUnitOrder(FVector Location, float YawRotation);

	//Для обычного юнита
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUnitEnemyReaction UnitEnemyReaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bForcedMarch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bConcentratedFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YawRotation;

	//Для разведчика
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> ExplorationLocations;

	//Для адъюданта
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<struct FAssignedUnitOrder> SentOrdersToUnits;
	

	bool IsSetToAttack();
	bool IsSetToDefend();
};