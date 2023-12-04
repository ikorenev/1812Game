#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnitOrder.h"
#include "TeamEnum.h"
#include "BaseUnit.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GAME1812_API ABaseUnit : public APawn
{
	GENERATED_BODY()

public:

	ABaseUnit();

protected:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	class UUnitMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETeam Team;

	FUnitOrder CurrentOrder;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void AssignOrder(FUnitOrder NewOrder);
	FUnitOrder GetCurrentOrder() { return CurrentOrder; };

	ETeam GetTeam() { return Team; };

	class UUnitMovementComponent* GetMovementComponent() { return MovementComponent; };

	float GetMovementSpeed();
	float GetRotationSpeed();
};
