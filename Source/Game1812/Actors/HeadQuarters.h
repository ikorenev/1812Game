#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/UnitOrder.h"
#include "../Pawns/OrderAndUnitContainer.h"
#include "HeadQuarters.generated.h"

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

	UPROPERTY(VisibleAnywhere)
	TArray<class AAdjutantUnit*> AvailableAdjutants;

	UPROPERTY(EditAnywhere)
	int AdjutantsAmount;


	static AHeadQuarters* Singleton;

public:	

	virtual void Tick(float DeltaTime) override;

	void AddAdjutantUnit(class AAdjutantUnit* AdjutantUnit) { AvailableAdjutants.Add(AdjutantUnit); };

	void AddOrderToAssign(const FUnitOrder& UnitOrder, class ABaseUnit* Unit);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static AHeadQuarters* GetSingleton();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HaveAnyOrders();

	UFUNCTION(BlueprintCallable)
	void SendOrders();

	class ABaseUnit* SpawnUnit(TSubclassOf<class ABaseUnit> UnitClass);
};
