#include "BaseUnit.h"

#include "UnitOrder.h"
#include "Components/UnitMovementComponent.h"
#include "../../Actors/HeadQuarters.h"

#include <Components/BoxComponent.h>

ABaseUnit::ABaseUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	BoxComponent->InitBoxExtent(FVector(10, 10, 5));
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RootComponent = BoxComponent;

	Team = ETeam::RUSSIA;

	Tags.Add("AffectedByFog");
}

void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	AddActorWorldOffset(FVector(0, 0, 10));
	AddActorWorldOffset(FVector(0, 0, -20), true);
}

ETeam ABaseUnit::GetTeam()
{
	return Team;
}

UUnitOrder* ABaseUnit::GetCurrentOrder()
{
	return nullptr;
}

void ABaseUnit::AssignOrder(UUnitOrder* NewOrder)
{

}