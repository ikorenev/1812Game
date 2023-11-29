#include "HeadQuarters.h"

#include "../Pawns/BaseUnit.h"

AHeadQuarters* AHeadQuarters::Singleton = nullptr;

AHeadQuarters* AHeadQuarters::GetSingleton()
{
	return Singleton;
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

ABaseUnit* AHeadQuarters::SpawnUnit(TSubclassOf<class ABaseUnit> UnitClass)
{
	FVector point = GetActorLocation();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return GetWorld()->SpawnActor<ABaseUnit>(UnitClass.Get(), point, FRotator(0, GetActorRotation().Yaw, 0), spawnParams);
}