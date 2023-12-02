#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/UnitOrder.h"
#include "HeadQuarters.generated.h"

USTRUCT(BlueprintType)
struct GAME1812_API FOrderAndUnitContainer
{
	GENERATED_BODY()

public: 

	FOrderAndUnitContainer();
	FOrderAndUnitContainer(const FUnitOrder& UnitOrder, class ABaseUnit* Unit);

	UPROPERTY(VisibleAnywhere)
	FUnitOrder UnitOrder;

	UPROPERTY(VisibleAnywhere)
	class ABaseUnit* Unit;
};

UCLASS()
class GAME1812_API AHeadQuarters : public AActor
{
	GENERATED_BODY()
	
public:	

	AHeadQuarters();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TArray<FOrderAndUnitContainer> UnitOrders;

	static AHeadQuarters* Singleton;

public:	

	virtual void Tick(float DeltaTime) override;

	void AddOrderToAssign(const FUnitOrder& UnitOrder, class ABaseUnit* Unit);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static AHeadQuarters* GetSingleton();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HaveAnyOrders();

	UFUNCTION(BlueprintCallable)
	void SendOrders();

	class ABaseUnit* SpawnUnit(TSubclassOf<class ABaseUnit> UnitClass);
};
