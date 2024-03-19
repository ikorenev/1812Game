#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Pawns/Unit/UnitOrder.h"
#include "../Pawns/Unit/AssignedUnitOrder.h"
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
	TArray<FAssignedUnitOrder> UnitOrders;

	UPROPERTY(VisibleAnywhere)
	TArray<class AAdjutantUnit*> AvailableAdjutants;

	UPROPERTY(EditAnywhere)
	int AdjutantsAmount;


	static AHeadQuarters* Instance;

public:	

	virtual void Tick(float DeltaTime) override;

	void AddAdjutantUnit(class AAdjutantUnit* AdjutantUnit) { AvailableAdjutants.Add(AdjutantUnit); };

	void AddOrderToAssign(const FUnitOrder& UnitOrder, class ABaseUnit* Unit);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static AHeadQuarters* GetInstance();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HaveAnyOrders();

	UFUNCTION(BlueprintCallable)
	void SendOrders();

	class ABaseUnit* SpawnUnit(TSubclassOf<class ABaseUnit> UnitClass);
};
