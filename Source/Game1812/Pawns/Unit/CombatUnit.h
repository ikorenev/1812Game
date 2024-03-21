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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUnitMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUnitCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UUnitReportComponent* ReportComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCombatUnitOrder* CurrentOrder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UCombatUnitDataAsset* CombatUnitData;

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:

	virtual void Tick(float DeltaTime) override;
	virtual void SpawnDefaultController() override;

	class UUnitCombatComponent* GetCombatComponent();

	class UUnitReportComponent* GetReportComponent();

	struct FCombatUnitStats* GetCombatUnitStats();

	void SetCombatUnitData(class UCombatUnitDataAsset* NewCombatUnitData);


	//ABaseUnit class override
	class UUnitMovementComponent* GetMovementComponent() override;

	float GetMovementSpeed() override;
	float GetRotationSpeed() override;

	class UUnitOrder* GetCurrentOrder();
	void AssignOrder(class UUnitOrder* NewOrder);
	//
	
	//IDamageable Interface
	float ApplyDamage(IDamageable* Attacker, float Amount) override;

	ETeam GetTeam() override;
	ECombatUnitType GetUnitType() override;
	FVector GetLocation() override;
	bool IsValidTarget() override;
	//
};
