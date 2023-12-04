#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME1812_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();

protected:

	class ABaseUnit* UnitPawn;

	UPROPERTY(VisibleAnywhere);
	float HealthPoints;

	class IDamageable* TargetedEnemy;

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetDamage() { return 10; };
	float GetAttackRange() { return 15; };
	float GetDetectionRange() { return 75; };

	void FindEnemiesInRange(TArray<class IDamageable*>& OutArray);
	class IDamageable* FindClosestEnemyInRange();

	void SetTargetedEnemy(class IDamageable* NewTarget);
};
