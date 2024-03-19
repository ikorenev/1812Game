#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnitOrder.h"
#include "TeamEnum.h"
#include "BaseUnit.generated.h"

UCLASS(Abstract, Blueprintable)
class GAME1812_API ABaseUnit : public APawn
{
	GENERATED_BODY()

public:

	ABaseUnit();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETeam Team;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FUnitOrder CurrentOrder;

	virtual void BeginPlay() override;

	virtual void OnOrderAssign(const FUnitOrder& NewOrder);

public:	

	ETeam GetTeam();
	FUnitOrder GetCurrentOrder();

	void AssignOrder(const FUnitOrder& NewOrder);
};
