#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "Components/MoveableUnit.h"
#include "AssignedUnitOrder.h"
#include "AdjutantUnit.generated.h"

UCLASS()
class GAME1812_API AAdjutantUnit : public ABaseUnit, public IMoveableUnit
{
	GENERATED_BODY()
	
public:

	AAdjutantUnit();

protected:

	UPROPERTY(VisibleAnywhere)
	class UUnitMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinDistanceToGiveOrder;

	UPROPERTY(VisibleAnywhere)
	TArray<FAssignedUnitOrder> Orders;

	virtual void BeginPlay() override;

	void OnOrderAssign(const FUnitOrder& NewOrder) override;

	void OnMovementComplete();

	void MoveToNextTarget();

	FAssignedUnitOrder FindClosestTarget();

public:

	class UUnitMovementComponent* GetMovementComponent();

	float GetMovementSpeed() override;
	float GetRotationSpeed() override;
	
};
