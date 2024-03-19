#pragma once

#include "CoreMinimal.h"
#include "UnitReport.generated.h"

USTRUCT(BlueprintType)
struct GAME1812_API FUnitReport
{

	GENERATED_USTRUCT_BODY();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AlliedLosses = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyLosses = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> Morale;

public:

	void Clear();

	float GetAlliedLosses() const;
	float GetEnemyLosses() const;
	float GetAverageMorale() const;

	void AddAlliedLosses(float AddedAlliedLosses);
	void AddEnemyLosses(float AddedEnemyLosses);
	void SetMorale(float NewMorale);

	FUnitReport& operator+(const FUnitReport& Other);
};
