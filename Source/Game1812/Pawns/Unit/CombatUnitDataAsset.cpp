#include "CombatUnitDataAsset.h"

FCombatUnitStats::FCombatUnitStats()
{
	MovementSpeed = 50.0f;
	RotationSpeed = 50.0f;
	BaseHP = 1000.0f;
	BaseDamage = 0.5f;
	BaseDefense = 0.5f;

	AttackDistance = 50.0f;
	EnemyDetectionRange = 500.0f;
}

float FCombatUnitStats::GetMovementSpeed()
{
	return MovementSpeed;
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

