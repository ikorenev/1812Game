#include "HeadQuarters.h"

#include "../Pawns/BaseUnit.h"

FOrderAndUnitContainer::FOrderAndUnitContainer() 
{
	Unit = nullptr;
}

FOrderAndUnitContainer::FOrderAndUnitContainer(const FUnitOrder& UnitOrder, ABaseUnit* Unit) 
{
	this->UnitOrder = UnitOrder;
	this->Unit = Unit;
}

AHeadQuarters* AHeadQuarters::Singleton = nullptr;

AHeadQuarters* AHeadQuarters::GetSingleton()
{
	return Singleton;
}

bool AHeadQuarters::HaveAnyOrders()
{
	return UnitOrders.Num() != 0;
}

void AHeadQuarters::SendOrders()
{
	for (auto el : UnitOrders) 
	{
		if (!el.Unit) continue;

		el.Unit->AssignOrder(el.UnitOrder);
	}

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
	
	Singleton = this;
}

void AHeadQuarters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeadQuarters::AddOrderToAssign(const FUnitOrder& UnitOrder, ABaseUnit* Unit) 
{
	UnitOrders.RemoveAll([&](const FOrderAndUnitContainer& el) { return el.Unit == Unit; });

	UnitOrders.Add(FOrderAndUnitContainer(UnitOrder, Unit));
}

ABaseUnit* AHeadQuarters::SpawnUnit(TSubclassOf<class ABaseUnit> UnitClass)
{
	FVector point = GetActorLocation();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return GetWorld()->SpawnActor<ABaseUnit>(UnitClass.Get(), point, FRotator(0, GetActorRotation().Yaw, 0), spawnParams);
}