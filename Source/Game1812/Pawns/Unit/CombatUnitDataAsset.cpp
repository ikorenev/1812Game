#include "CombatUnitDataAsset.h"

FCombatUnitStats::FCombatUnitStats()
{
	MaxMovementSpeed = 25.0f;
	MinMovementSpeed = 5.0f;
	RotationSpeed = 50.0f;
	BaseHP = 1000.0f;
	BaseDamage = 0.5f;
	BaseDefense = 0.5f;
	MoraleRestorationSpeed = 0.1f;
	DistanceForFullMoraleLoss = 1500.f;
	AttackDistance = 10.0f;
	EnemyDetectionRange = 500.0f;
}

float FCombatUnitStats::GetMaxMovementSpeed()
{
	return MaxMovementSpeed;
}

float FCombatUnitStats::GetMinMovementSpeed()
{
	return MinMovementSpeed;
}

float FCombatUnitStats::GetRotationSpeed()
{
	return RotationSpeed;
}

float FCombatUnitStats::GetBaseHP()
{
	return BaseHP;
}

float FCombatUnitStats::GetBaseDamage()
{
	return BaseDamage;
}

float FCombatUnitStats::GetBaseDefense()
{
	return BaseDefense;
}

float FCombatUnitStats::GetMoraleRestorationSpeed()
{
	return MoraleRestorationSpeed;
}

float FCombatUnitStats::GetDistanceForFullMoraleLoss()
{
	return DistanceForFullMoraleLoss;
}

float FCombatUnitStats::GetAttackDistance()
{
	return AttackDistance;
}

float FCombatUnitStats::GetEnemyDetectionRange()
{
	return EnemyDetectionRange;
}

UCombatUnitDataAsset::UCombatUnitDataAsset()
{
	UnitName = "Unnamed Unit";
	CombatUnitStats = FCombatUnitStats();
	PieceMesh = nullptr;
	PieceFoundationMesh = nullptr;
}

FName UCombatUnitDataAsset::GetName()
{
	return UnitName;
}

FCombatUnitStats* UCombatUnitDataAsset::GetCombatUnitStats() 
{
	return &CombatUnitStats;
}

UStaticMesh* UCombatUnitDataAsset::GetPieceMesh()
{
	return PieceMesh;
}

UStaticMesh* UCombatUnitDataAsset::GetPieceFoundationMesh()
{
	return PieceFoundationMesh;
}

