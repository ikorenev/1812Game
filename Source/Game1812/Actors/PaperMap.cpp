#include "PaperMap.h"

#include <Components/BoxComponent.h>

APaperMap::APaperMap()
{
	PrimaryActorTick.bCanEverTick = false;

	PaperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paper Mesh"));
	PaperMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	RootComponent = PaperMeshComponent;

	BordersHeight = 250.f;
}

void APaperMap::BeginPlay()
{
	Super::BeginPlay();
	
	//FVector mapBordersExtent = PaperMeshComponent->CalcBounds(PaperMeshComponent->GetComponentTransform()).BoxExtent;
	//mapBordersExtent /= GetActorScale3D();
	//mapBordersExtent.Z = BordersHeight;
	//MapBordersComponent->InitBoxExtent(mapBordersExtent);
}
