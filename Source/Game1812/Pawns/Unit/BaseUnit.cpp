#include "BaseUnit.h"

#include <Components/BoxComponent.h>

#include "Components/UnitMovementComponent.h"
#include "CombatUnitStats.h"
#include "../../Actors/HeadQuarters.h"

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

	CurrentOrder = FUnitOrder(GetActorLocation(), GetActorRotation().Yaw);
}

ETeam ABaseUnit::GetTeam()
{
	return Team;
}

FUnitOrder ABaseUnit::GetCurrentOrder()
{
	return CurrentOrder;
}

void ABaseUnit::AssignOrder(const FUnitOrder& NewOrder)
{
	CurrentOrder = NewOrder;

	OnOrderAssign(NewOrder);
}

void ABaseUnit::OnOrderAssign(const FUnitOrder& NewOrder) { }