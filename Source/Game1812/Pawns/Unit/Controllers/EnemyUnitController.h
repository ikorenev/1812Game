#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "EnemyUnitController.generated.h"


UCLASS()
class GAME1812_API AEnemyUnitController : public AController
{
	GENERATED_BODY()
	
public:

	AEnemyUnitController();

protected:

	TWeakObjectPtr<class ACombatUnit> CombatUnit;

	void OnPossess(APawn* InPawn) override;

public:

	
};
