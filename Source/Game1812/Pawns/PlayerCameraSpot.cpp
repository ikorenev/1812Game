#include "PlayerCameraSpot.h"

// Sets default values
APlayerCameraSpot::APlayerCameraSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCameraSpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCameraSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

