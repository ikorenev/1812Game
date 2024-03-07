#include "HeadQuarters.h"

#include "../Pawns/Unit/BaseUnit.h"
#include "../Pawns/Unit/AdjutantUnit.h"
#include "../CossacksGameInstance.h"

AHeadQuarters* AHeadQuarters::Instance = nullptr;

AHeadQuarters* AHeadQuarters::GetInstance()
{
	return Instance;
}

bool AHeadQuarters::HaveAnyOrders()
{
	return UnitOrders.Num() != 0;
}

void AHeadQuarters::SendOrders()
{
	if (AvailableAdjutants.IsEmpty())
		return;

	UAdjutantUnitOrder* unitOrder = NewObject<UAdjutantUnitOrder>();
	unitOrder->SentOrdersToUnits = UnitOrders;

	AvailableAdjutants[0]->AssignOrder(unitOrder);
	AvailableAdjutants.RemoveAt(0);

	UnitOrders.Empty();
}

AHeadQuarters::AHeadQuarters()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));

}

void AHeadQuarters::BeginPlay()
{
	Super::BeginPlay();
	
	Instance = this;

	UCossacksGameInstance* gameInstance = GetGameInstance<UCossacksGameInstance>();

	if (!gameInstance)
		return;

	for (int i = 0; i < AdjutantsAmount; i++) 
	{
		ABaseUnit* unit = SpawnUnit(gameInstance->AdjutantUnitClass);

		AAdjutantUnit* adjutantUnit = Cast<AAdjutantUnit>(unit);

		if (adjutantUnit) 
		{
			AvailableAdjutants.Add(adjutantUnit);
		}
	}
}

void AHeadQuarters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeadQuarters::AddOrderToAssign(class UCombatUnitOrder* UnitOrder, ABaseUnit* Unit)
{
	UnitOrders.RemoveAll([&](const FAssignedCombatUnitOrder& el) { return el.Unit == Unit; });

	UnitOrders.Add(FAssignedCombatUnitOrder(UnitOrder, Unit));
}

ABaseUnit* AHeadQuarters::SpawnUnit(TSubclassOf<class ABaseUnit> UnitClass)
{
	FVector point = GetActorLocation();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return GetWorld()->SpawnActor<ABaseUnit>(UnitClass.Get(), point, FRotator(0, GetActorRotation().Yaw, 0), spawnParams);
}