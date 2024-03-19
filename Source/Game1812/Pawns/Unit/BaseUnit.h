#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../../Actors/FogAffected.h"
#include "TeamEnum.h"
#include "BaseUnit.generated.h"

UCLASS(Abstract, Blueprintable)
class GAME1812_API ABaseUnit : public APawn, public IFogAffected
{
	GENERATED_BODY()

public:

	ABaseUnit();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETeam Team;

	virtual void BeginPlay() override;

public:	

	virtual class UUnitMovementComponent* GetMovementComponent();

	virtual float GetMovementSpeed();
	virtual float GetRotationSpeed();

	ETeam GetTeam();

	//IFogAffected Interface
	void OnBeingCoveredInFog() override;
	void OnBeingRevealedFromFog() override;
	bool IsCoveredInFog() override;
	//


	virtual class UUnitOrder* GetCurrentOrder();
	virtual void AssignOrder(class UUnitOrder* NewOrder);
};
