#include "PieceMapMarker.h"

APieceMapMarker::APieceMapMarker()
{
	PrimaryActorTick.bCanEverTick = true;

	MapMarkerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker Mesh"));
	MapMarkerMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MapMarkerMeshComponent;
}

void APieceMapMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

void APieceMapMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

