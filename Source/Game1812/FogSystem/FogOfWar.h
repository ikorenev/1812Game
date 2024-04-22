#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssetUtils/Texture2DBuilder.h"
#include "Image/ImageBuilder.h"
#include "FogOfWar.generated.h"

using namespace UE::Geometry;

void ApplyCircularBrushToImage(TImageBuilder<FVector4f>& Image, )
{

}

USTRUCT()
struct GAME1812_API FFogDiscoveredArea
{
	GENERATED_BODY()

public:

	FFogDiscoveredArea();
	FFogDiscoveredArea(const FFogDiscoveredArea& Other);
	FFogDiscoveredArea(FImageDimensions AreaDimensions, float Time);

	TImageBuilder<FVector4f> DiscoveredArea;

	UPROPERTY(VisibleAnywhere)
	float DiscoverEndTime;

	//friend bool operator==(const FFogDiscoveredArea& First, const FFogDiscoveredArea& Second);
};

UCLASS()
class GAME1812_API AFogOfWar : public AActor
{
	GENERATED_BODY()
	
public:	

	AFogOfWar();

protected:

	static AFogOfWar* Instance;

	//Scene components
	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* FogArea;

	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* NiagaraFogComponent;
	//

	UPROPERTY(EditAnywhere)
	bool AffectActors;

	UPROPERTY(VisibleDefaultsOnly)
	FIntPoint Resolution;

	UPROPERTY(VisibleAnywhere)
	TArray<FFogDiscoveredArea> TimedDiscoveredAreas;

	TImageBuilder<FVector4f> ConstantDiscoveredArea;
	TImageBuilder<FVector4f> FogAlphaImageBuilder;

	UPROPERTY(VisibleAnywhere)
	UTexture2D* FogAlphaTexture;

	virtual void BeginPlay() override;

	void UpdateFogTexture();

	void UpdateDiscoveredAreas();

	void CheckActorsInFog();
	

	static void AddTextureToTexture(TImageBuilder<FVector4f>& MainImage, const TImageBuilder<FVector4f>& Image);

public:	

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static AFogOfWar* GetInstance();

	FVector GetChunkSize();

	FIntPoint LocationToIndex(FVector Location);

	virtual void Tick(float DeltaTime) override;
};
