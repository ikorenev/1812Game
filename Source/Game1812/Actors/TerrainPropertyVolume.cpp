#include "TerrainPropertyVolume.h"

#include "../DataAssets/TerrainPropertyDataAsset.h"

#include <Components/BoxComponent.h>
#include <NavModifierComponent.h>

ATerrainPropertyVolume::ATerrainPropertyVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Terrain Volume"));
	BoxComponent->SetCollisionProfileName("OverlapAll");
	BoxComponent->SetGenerateOverlapEvents(true);
	
	NavModifierComponent = CreateDefaultSubobject<UNavModifierComponent>(TEXT("Navigation Mesh Modifier"));
}

#if WITH_EDITOR
void ATerrainPropertyVolume::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName propertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (propertyName == GET_MEMBER_NAME_CHECKED(ATerrainPropertyVolume, TerrainPropertyDataAsset))
	{
		if (!TerrainPropertyDataAsset)
			return;

		NavModifierComponent->AreaClass = TerrainPropertyDataAsset->GetTerrainNavAreaClass();
	}
}
#endif