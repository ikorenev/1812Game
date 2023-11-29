#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeadQuarters.generated.h"

UCLASS()
class GAME1812_API AHeadQuarters : public AActor
{
	GENERATED_BODY()
	
public:	

	AHeadQuarters();

protected:

	virtual void BeginPlay() override;

	static AHeadQuarters* Singleton;

public:	

	virtual void Tick(float DeltaTime) override;

	static AHeadQuarters* GetSingleton();

	class ABaseUnit* SpawnUnit(TSubclassOf<class ABaseUnit> UnitClass);
};
