#include "UnitDeathNotifier.h"

AUnitDeathNotifier::AUnitDeathNotifier()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AUnitDeathNotifier::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnitDeathNotifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnitDeathNotifier::OnBeingCoveredInFog()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void AUnitDeathNotifier::OnBeingRevealedFromFog()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool AUnitDeathNotifier::IsCoveredInFog()
{
	throw std::logic_error("The method or operation is not implemented.");
}

