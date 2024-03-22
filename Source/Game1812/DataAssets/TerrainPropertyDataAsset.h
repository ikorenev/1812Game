#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../Pawns/Unit/CombatUnitType.h"
#include "../Actors/NavArea_CustomTerrain.h"
#include "TerrainPropertyDataAsset.generated.h"

UCLASS()
class GAME1812_API UTerrainPropertyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UTerrainPropertyDataAsset();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECombatUnitType, float> MovementSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECombatUnitType, float> MovementRotationMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECombatUnitType, float> DamageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<ECombatUnitType, float> DefenseMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UNavArea_CustomTerrain> TerrainNavAreaClass;

public:

	float GetMovementSpeedMultiplier(ECombatUnitType CombatUnitType) const;
	float GetMovementRotationMultiplier(ECombatUnitType CombatUnitType) const;
	float GetDamageMultiplier(ECombatUnitType CombatUnitType) const;
	float GetDefenseMultiplier(ECombatUnitType CombatUnitType) const;
	const TSubclassOf<UNavArea_CustomTerrain>& GetTerrainNavAreaClass() const;
};
