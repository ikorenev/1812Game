#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAME1812_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UCombatComponent();

protected:

	class ACombatUnit* CombatUnitPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HealthPoints;

	TWeakInterfacePtr<class IDamageable> TargetedEnemy;

	virtual void BeginPlay() override;

	void SetTargetedEnemy(class IDamageable* NewTarget);

	void TryAttack(class IDamageable* Target, float DeltaTime);
	void Attack(class IDamageable* Target, float DeltaTime);
	bool CanAttack(class IDamageable* Target);

	void FindEnemiesInRange(TArray<class IDamageable*>& OutArray);
	class IDamageable* FindClosestEnemyInRange();

public:	

	float GetBaseDamage();
	float GetAttackRange();
	float GetDetectionRange();

	void Init(struct FCombatUnitStats* UnitCombatStats);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyDamage(UCombatComponent* Attacker, float DamageAmount);
	
};
