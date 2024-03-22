#include "TerrainPropertyDataAsset.h"



UTerrainPropertyDataAsset::UTerrainPropertyDataAsset()
{
	
}

float UTerrainPropertyDataAsset::GetMovementSpeedMultiplier(ECombatUnitType CombatUnitType) const
{
	return 0.0f;
}

float UTerrainPropertyDataAsset::GetMovementRotationMultiplier(ECombatUnitType CombatUnitType) const
{
	return 0.0f;
}

float UTerrainPropertyDataAsset::GetDamageMultiplier(ECombatUnitType CombatUnitType) const
{
	return 0.0f;
}

float UTerrainPropertyDataAsset::GetDefenseMultiplier(ECombatUnitType CombatUnitType) const
{
	return 0.0f;
}

const TSubclassOf<UNavArea_CustomTerrain>& UTerrainPropertyDataAsset::GetTerrainNavAreaClass() const
{
	return TerrainNavAreaClass;
}
