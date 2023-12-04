#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "Components/Damageable.h"
#include "CombatUnit.generated.h"

UCLASS()
class GAME1812_API ACombatUnit : public ABaseUnit, public IDamageable
{
	GENERATED_BODY()

public:

	ACombatUnit();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCombatComponent* CombatComponent;

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	void AssignOrder(FUnitOrder NewOrder) override;


	void ApplyDamage(class UCombatComponent* Attacker, float Amount) override;

	ETeam GetTeam() override;

	bool IsDead() override;

	FVector GetLocation() override;
};
