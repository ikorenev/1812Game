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

	Team = ETeam::Russia;

	Tags.Add("AffectedByFog");
}

void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	AddActorWorldOffset(FVector(0, 0, 10));
	AddActorWorldOffset(FVector(0, 0, -20), true);
}

UUnitMovementComponent* ABaseUnit::GetMovementComponent()
{
	return nullptr;
}

float ABaseUnit::GetMovementSpeed()
{
	return 0.0f;
}

float ABaseUnit::GetRotationSpeed()
{
	return 0.0f;
}

ETeam ABaseUnit::GetTeam()
{
	return Team;
}

void ABaseUnit::OnBeingCoveredInFog()
{
	SetActorHiddenInGame(true);
}

void ABaseUnit::OnBeingRevealedFromFog()
{
	SetActorHiddenInGame(false);
}

bool ABaseUnit::IsCoveredInFog()
{
	return IsHidden();
}

UUnitOrder* ABaseUnit::GetCurrentOrder()
{
	return nullptr;
}

void ABaseUnit::AssignOrder(UUnitOrder* NewOrder)
{

}