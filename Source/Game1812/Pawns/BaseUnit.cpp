#include "BaseUnit.h"

#include <GameFramework/CharacterMovementComponent.h>
#include <NavigationPath.h>
#include <NavigationSystem.h>
#include <AITypes.h>
#include <AIController.h>

ABaseUnit::ABaseUnit()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UCharacterMovementComponent >(FName("Movement Component"));


}

void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultController();
	
}

void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseUnit::MoveToLocation(FVector location)
{
	
	UNavigationPath* path = UNavigationSystemV1::FindPathToLocationSynchronously(this, GetActorLocation(), location, this);
	
	if (path && path->IsValid())
	{
		FAIMoveRequest req;
		req.SetAcceptanceRadius(1);
		req.SetUsePathfinding(true);

		AAIController* ai = Cast<AAIController>(GetController());

		if (ai)
		{
			ai->RequestMove(req, path->GetPath());
		}
	}
}