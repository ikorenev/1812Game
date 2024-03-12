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
	float MaxMovementSpeed = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinMovementSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseHP = 1000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDamage = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseDefense = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoraleRestorationSpeed = 0.1f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoraleLossDueToLosses = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DistanceForFullMoraleLoss = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDistance = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyDetectionRange = 200.0f;

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
