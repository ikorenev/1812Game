#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "AssignedUnitOrder.h"
#include "AdjutantUnit.generated.h"

UCLASS()
class GAME1812_API AAdjutantUnit : public ABaseUnit
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

	UPROPERTY(VisibleAnywhere)
	TArray<FAssignedCombatUnitOrder> Orders;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMovementComplete();

	void MoveToNextTarget();

	FAssignedCombatUnitOrder FindClosestTarget();

public:

	class UUnitOrder* GetCurrentOrder();
	void AssignOrder(class UUnitOrder* NewOrder);

	class UUnitMovementComponent* GetMovementComponent();

	float GetMovementSpeed() override;
	float GetRotationSpeed() override;
	
};
