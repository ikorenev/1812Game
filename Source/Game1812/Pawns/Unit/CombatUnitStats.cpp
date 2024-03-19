#include "CombatUnitStats.h"

FCombatUnitStats::FCombatUnitStats()
{
	MovementSpeed = 50.0f;
	RotationSpeed = 50.0f;
	StartHP = 1000.0f;
	BaseDamage = 0.5f;
	BaseDefense = 0.5f;

	AttackDistance = 50.f;
	EnemyDetectionRange = 500.f;
}

FCombatUnitContainer UCombatUnitsTable::FindUnitStatsByType(ECombatUnitType CombatUnitType)
{
	FCombatUnitContainer* ret = Units.FindByPredicate([&](const FCombatUnitContainer& el)
		{
			return (el.UnitType == CombatUnitType);
		});

	if (ret)
		return *ret;

	return FCombatUnitContainer();
}
