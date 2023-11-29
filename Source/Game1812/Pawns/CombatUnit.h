#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "CombatUnit.generated.h"

UCLASS()
class GAME1812_API ACombatUnit : public ABaseUnit
{
	GENERATED_BODY()


public:

	ACombatUnit();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void AssignOrder(FUnitOrder NewOrder) override;
};
