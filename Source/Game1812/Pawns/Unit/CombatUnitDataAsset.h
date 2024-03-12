#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatUnitDataAsset.generated.h"

USTRUCT(BlueprintType)
struct GAME1812_API FCombatUnitStats
{
	GENERATED_USTRUCT_BODY()

public:

	FCombatUnitStats();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseHP; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDefense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoraleRestorationSpeed; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoraleLossDueToLosses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceForFullMoraleLoss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyDetectionRange;

public:

	float GetMaxMovementSpeed();
	float GetMinMovementSpeed();
	float GetRotationSpeed();
	float GetBaseHP();
	float GetAttackCooldown();
	float GetBaseDamage();
	float GetBaseDefense();
	float GetMoraleRestorationSpeed();
	float GetMoraleLossDueToLosses();
	float GetDistanceForFullMoraleLoss();
	float GetAttackDistance();
	float GetEnemyDetectionRange();

};

UCLASS(BlueprintType)
class GAME1812_API UCombatUnitDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UCombatUnitDataAsset();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName UnitName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCombatUnitStats CombatUnitStats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* PieceMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh* PieceFoundationMesh;

public:

	FName GetName();
	FCombatUnitStats* GetCombatUnitStats();
	UStaticMesh* GetPieceMesh();
	UStaticMesh* GetPieceFoundationMesh();
	
};
