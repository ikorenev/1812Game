#include "CombatUnitDataAsset.h"

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

float FCombatUnitStats::GetAttackCooldown()
{
	return AttackCooldown;
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

float FCombatUnitStats::GetMoraleLossDueToLosses()
{
	return MoraleLossDueToLosses;
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

