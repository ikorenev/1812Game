#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitCombatComponent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAME1812_API UUnitCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UUnitCombatComponent();

protected:

	class ACombatUnit* CombatUnitPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HealthPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Morale;

	float TimeOfLastAttack;

	TWeakInterfacePtr<class IDamageable> TargetedEnemy;

	virtual void BeginPlay() override;

	void SetTargetedEnemy(class IDamageable* NewTarget);

	void AddMorale(float Amount);

	UFUNCTION()
	void OnPawnMove(float Distance);
	void OnBeingAttacked(class IDamageable* Attacker);

	void TryAttack(class IDamageable* Target, float DeltaTime);
	bool CanAttack(class IDamageable* Target);
	void Attack(class IDamageable* Target, float DeltaTime);

	void UpdateMoraleRestoration(float DeltaTime);

	void FindEnemiesInRange(TArray<class IDamageable*>& OutArray);
	class IDamageable* FindClosestEnemyInRange();

	bool IsTargetInRange(IDamageable* Target);
	
public:	

	float GetAttackCooldown();
	float GetBaseDamage();
	float GetBaseDefense();
	float GetAttackRange();
	float GetDetectionRange();

	float CalculateDamage();
	float CalculateDefense();
	float CalculateMovementSpeed();

	

	void Init(struct FCombatUnitStats* UnitCombatStats);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ApplyDamage(class IDamageable* Attacker, float DamageAmount);
	
};
