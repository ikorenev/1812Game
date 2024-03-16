#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../CombatUnitType.h"
#include "UnitCombatComponent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAME1812_API UUnitCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UUnitCombatComponent();

protected:

	class ACombatUnit* CombatUnitPawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit Combat")
	float HealthPoints;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit Combat")
	float Morale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Unit Combat")
	bool bIsTemporarilyDefeated;

	float TimeOfLastAttack;

	float TimeOfLastTakenDamage;

	TWeakInterfacePtr<class IDamageable> TargetedEnemy;

	virtual void BeginPlay() override;

	class UCombatUnitOrder* GetCombatUnitOrder();

	void SetTargetedEnemy(class IDamageable* NewTarget);

	void AddMorale(float Amount);

	UFUNCTION()
	void OnPawnMove(float Distance);
	void OnBeingAttackedBehaviour(class IDamageable* Attacker);

	void TryAttack(class IDamageable* Target);
	bool CanAttack(class IDamageable* Target);
	void Attack(class IDamageable* Target);

	void UpdateMoraleRestoration(float DeltaTime);
	void UpdateTempDefeat();
	void UpdateOrderBehaviour();
	void UpdateTargetAttack();

	void FindEnemiesInRange(TArray<class IDamageable*>& OutArray);
	class IDamageable* FindClosestEnemyInRange();

	FVector FindRetreatDirection();

	bool IsTargetInDetectionRange(IDamageable* Target);
	bool IsTargetInAttackRange(IDamageable* Target);
	
public:	

	float GetAttackCooldown() const;
	float GetBaseDamage() const;
	float GetBaseDefense() const;
	float GetAttackRange() const;
	float GetDetectionRange() const;

	float GetDamageMultiplier(ECombatUnitType AttackedUnitType) const;
	float GetDefenseMultiplier(ECombatUnitType AttackerUnitType) const;

	float CalculateDamage(ECombatUnitType AttackedUnitType) const;
	float CalculateDefense(ECombatUnitType AttackerUnitType) const;

	float CalculateMovementSpeed();
	float CalculateRotationSpeed();

	void Init(struct FCombatUnitStats* UnitCombatStats);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void ApplyDamage(class IDamageable* Attacker, float DamageAmount);
	
};
