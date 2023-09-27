#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseUnit.generated.h"

UCLASS()
class GAME1812_API ABaseUnit : public APawn
{
	GENERATED_BODY()

public:

	ABaseUnit();

protected:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	FVector TargetLocation;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	void MoveToLocation(FVector location);

};
