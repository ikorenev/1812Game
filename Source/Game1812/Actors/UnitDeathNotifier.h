#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogAffected.h"
#include "UnitDeathNotifier.generated.h"

UCLASS()
class GAME1812_API AUnitDeathNotifier : public AActor, public IFogAffected
{
	GENERATED_BODY()
	
public:	

	AUnitDeathNotifier();

protected:

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void OnBeingCoveredInFog() override;


	void OnBeingRevealedFromFog() override;


	bool IsCoveredInFog() override;

};
