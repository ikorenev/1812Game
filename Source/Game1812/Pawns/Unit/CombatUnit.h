#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"

#include "Components/MoveableUnit.h"
#include "Components/Damageable.h"

#include "CombatUnitStats.h"
#include "CombatUnitEnum.h"

#include "CombatUnit.generated.h"

UCLASS()
class GAME1812_API ACombatUnit : public ABaseUnit, public IMoveableUnit, public IDamageable
{
	GENERATED_BODY()

public:

	ACombatUnit();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUnitMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCombatUnitOrder* CurrentOrder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCombatUnitDataAsset* CombatUnitData;

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	struct FCombatUnitStats* GetCombatUnitStats();

	void SetCombatUnitData(class UCombatUnitDataAsset* NewCombatUnitData);

	//ABaseUnit class override
	class UUnitOrder* GetCurrentOrder();
	void AssignOrder(class UUnitOrder* NewOrder);
	//
	
	//IMoveableUnit Interface
	class UUnitMovementComponent* GetMovementComponent();

	float GetMovementSpeed() override;
	float GetRotationSpeed() override;
	//
	
	//IDamageable Interface
	void ApplyDamage(class UCombatComponent* Attacker, float Amount) override;

	ETeam GetTeam() override;
	FVector GetLocation() override;
	//
};
