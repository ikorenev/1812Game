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

	class ABaseUnit* UnitPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	float HealthPoints;

	UPROPERTY(VisibleAnywhere);
	bool Dead;

	class IDamageable* TargetedEnemy;

	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void TryAttack(class IDamageable* Target, float DeltaTime);
	void Attack(class IDamageable* Target, float DeltaTime);
	bool CanAttack(class IDamageable* Target);

	void ApplyDamage(UCombatComponent* Attacker, float DamageAmount);

	float GetBaseDamage() { return 0.5f; };
	float GetAttackRange() { return 15; };
	float GetDetectionRange() { return 75; };

	bool IsDead() { return Dead; };

	void FindEnemiesInRange(TArray<class IDamageable*>& OutArray);
	class IDamageable* FindClosestEnemyInRange();

	void SetTargetedEnemy(class IDamageable* NewTarget);
};
