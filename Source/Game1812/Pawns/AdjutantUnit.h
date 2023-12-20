#pragma once

#include "CoreMinimal.h"
#include "BaseUnit.h"
#include "OrderAndUnitContainer.h"
#include "AdjutantUnit.generated.h"

UCLASS()
class GAME1812_API AAdjutantUnit : public ABaseUnit
{
	GENERATED_BODY()
	
public:

	AAdjutantUnit();

	

protected:

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	float InteractionDistance;

	UPROPERTY(VisibleAnywhere)
	TArray<FOrderAndUnitContainer> Orders;

	virtual void BeginPlay() override;

public:

	void TaskOrders(const TArray<FOrderAndUnitContainer>& NewOrders);

	void OnMovementComplete();
	void MoveToNextTarget();
	const FOrderAndUnitContainer& FindClosestTarget();

	float GetMovementSpeed() override;
	float GetRotationSpeed() override;
};
