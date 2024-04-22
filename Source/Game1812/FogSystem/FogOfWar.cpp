#include "FogOfWar.h"

#include "FogAffected.h"

#include <Components/BoxComponent.h>
#include <NiagaraComponent.h>
#include <NiagaraFunctionLibrary.h>
#include <Kismet/GameplayStatics.h>

FFogDiscoveredArea::FFogDiscoveredArea()
{
	DiscoverEndTime = 0.f;
}

FFogDiscoveredArea::FFogDiscoveredArea(const FFogDiscoveredArea& Other)
{
	DiscoveredArea = Other.DiscoveredArea;
	DiscoverEndTime = Other.DiscoverEndTime;
}

FFogDiscoveredArea::FFogDiscoveredArea(FImageDimensions AreaDimensions, float Time)
{
	DiscoveredArea.SetDimensions(AreaDimensions);
	DiscoverEndTime = Time;
}

//bool operator==(const FFogDiscoveredArea& First, const FFogDiscoveredArea& Second)
//{
//	return First.TextureBuilder == Second.TextureBuilder;
//}

AFogOfWar* AFogOfWar::Instance = nullptr;

AFogOfWar* AFogOfWar::GetInstance()
{
	return Instance;
}

AFogOfWar::AFogOfWar()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	FogArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Fog Area"));
	FogArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FogArea->SetupAttachment(RootComponent);

	NiagaraFogComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Fog"));
	NiagaraFogComponent->SetupAttachment(RootComponent);

	AffectActors = true;
}

void AFogOfWar::BeginPlay()
{
	Super::BeginPlay();

	Instance = this;
	Resolution = FIntPoint(512, 512);

	const FImageDimensions dimensions(Resolution.X, Resolution.Y);

	ConstantDiscoveredArea.SetDimensions(dimensions);
	ConstantDiscoveredArea.Clear(FVector4f::Zero());

	FogAlphaImageBuilder.SetDimensions(dimensions);
	FogAlphaImageBuilder.Clear(FVector4f::Zero());

	ConstantDiscoveredArea.SetPixel(FVector2i(2, 2), FVector4f::One());

	UpdateFogTexture();
}

void AFogOfWar::UpdateFogTexture()
{
	FogAlphaImageBuilder.Clear(FVector4f::Zero());

	AddTextureToTexture(FogAlphaImageBuilder, ConstantDiscoveredArea);

	for (FFogDiscoveredArea& area : TimedDiscoveredAreas)
	{
		AddTextureToTexture(FogAlphaImageBuilder, area.DiscoveredArea);
	}

	FTexture2DBuilder fogAlphaTextureBuilder;
	fogAlphaTextureBuilder.Initialize(FTexture2DBuilder::ETextureType::ColorLinear, FImageDimensions(Resolution.X, Resolution.Y));
	fogAlphaTextureBuilder.Copy(FogAlphaImageBuilder);
	fogAlphaTextureBuilder.Commit(false);
	FogAlphaTexture = fogAlphaTextureBuilder.GetTexture2D();
}

void AFogOfWar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateDiscoveredAreas();

	CheckActorsInFog();
}

void AFogOfWar::CheckActorsInFog()
{
	TArray<AActor*> affectedActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UFogAffected::StaticClass(), affectedActors);

	for (AActor* actor : affectedActors)
	{
		if (!actor)
			continue;

		IFogAffected* fogAffected = Cast<IFogAffected>(actor);

		if (!fogAffected)
			continue;

		FIntPoint index = LocationToIndex(actor->GetActorLocation());

		const bool isFogDisabled = FogAlphaImageBuilder.GetPixel(FVector2i(index.X, index.Y)).W > 0.75f;
		const bool isActorInFog = fogAffected->IsCoveredInFog();

		if (isFogDisabled && isActorInFog || !AffectActors)
		{
			fogAffected->OnBeingRevealedFromFog();
		}
		else if (!isFogDisabled && !isActorInFog)
		{
			fogAffected->OnBeingCoveredInFog();
		}
	}
}

void AFogOfWar::UpdateDiscoveredAreas()
{
	const float timeSeconds = GetWorld()->GetTimeSeconds();
	bool shouldUpdateTexture = false;

	for (int i = 0; i < TimedDiscoveredAreas.Num();)
	{
		if (TimedDiscoveredAreas[i].DiscoverEndTime < timeSeconds) 
		{
			TimedDiscoveredAreas.RemoveAt(i);
			shouldUpdateTexture = true;
		}
		else 
		{
			i++;
		}
	}

	if (shouldUpdateTexture)
		UpdateFogTexture();
}

FVector AFogOfWar::GetChunkSize()
{
	const FVector AreaSize = FogArea->GetScaledBoxExtent() * 2;
	const FVector SystemSize(AreaSize.X / Resolution.X, AreaSize.Y / Resolution.Y, AreaSize.Z);
	return SystemSize;
}

FIntPoint AFogOfWar::LocationToIndex(FVector Location)
{
	const FVector ChunkSize = GetChunkSize();
	const FVector RelativeLocation = Location - GetActorLocation() + FogArea->GetScaledBoxExtent();
	FIntPoint ret(RelativeLocation.X / ChunkSize.X, RelativeLocation.Y / ChunkSize.Y);

	ret.X = FMath::Clamp(ret.X, 0, Resolution.X - 1);
	ret.Y = FMath::Clamp(ret.Y, 0, Resolution.Y - 1);

	return ret;
}

void AFogOfWar::AddTextureToTexture(TImageBuilder<FVector4f>& MainImage, const TImageBuilder<FVector4f>& Image)
{
	if (MainImage.GetDimensions() != Image.GetDimensions())
		return;

	for (int x = 0; x < MainImage.GetDimensions().GetWidth(); x++)
	{
		for (int y = 0; y < MainImage.GetDimensions().GetHeight(); y++)
		{
			const FVector2i coords(x, y);
			const FVector4f newColor = MainImage.GetPixel(coords) + Image.GetPixel(coords);
			MainImage.SetPixel(coords, newColor);
		}
	}
}