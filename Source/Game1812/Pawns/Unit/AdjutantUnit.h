#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "Components/Damageable.h"
#include "AdjutantUnit.generated.h"

UCLASS()
class GAME1812_API AAdjutantUnit : public ABaseUnit, public IDamageable
{
	GENERATED_BODY()
	
public:

	AAdjutantUnit();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUnitMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UAdjutantUnitOrder* CurrentOrder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinDistanceToGiveOrder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DeathCooldown;

	FTimerHandle DeathCooldownTimer;

	UPROPERTY(VisibleAnywhere)
	TArray<struct FAssignedCombatUnitOrder> Orders;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMovementComplete();

	void MoveToNextTarget();

	UFUNCTION()
	void OnDeathCooldownEnd();

	struct FAssignedCombatUnitOrder FindClosestTarget();

public:

	bool IsOnDeathCooldown();
	bool IsInReachToInteractWithActor(AActor* Actor);
	
	void ForceReturnToHQ();

	//ABaseUnit class override
	class UUnitMovementComponent* GetMovementComponent();

	float GetMovementSpeed() override;
	float GetRotationSpeed() override;

	class UUnitOrder* GetCurrentOrder();
	void AssignOrder(class UUnitOrder* NewOrder);
	//

	//IDamageable Interface
	void ApplyDamage(IDamageable* Attacker, float Amount) override;

	ETeam GetTeam() override;
	ECombatUnitType GetUnitType() override;
	FVector GetLocation() override;
	bool IsValidTarget() override;
	//
};
