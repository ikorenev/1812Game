#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AssetUtils/Texture2DBuilder.h"
#include "FogOfWar.generated.h"

using namespace UE::Geometry;

USTRUCT()
struct GAME1812_API FFogTimer 
{
	GENERATED_BODY()

public:

	FFogTimer();
	FFogTimer(const FFogTimer& Other);
	FFogTimer(class UNiagaraComponent* FogComponent, float Timer);

	class UNiagaraComponent* FogComponent;

	UPROPERTY(VisibleAnywhere)
	float Timer;

	friend bool operator==(const FFogTimer & First, const FFogTimer & Second);
};

UCLASS()
class GAME1812_API AFogOfWar : public AActor
{
	GENERATED_BODY()
	
public:	

	AFogOfWar();

protected:

	static AFogOfWar* Singleton;

	UPROPERTY(VisibleDefaultsOnly)
	class UBoxComponent* FogArea;

	UPROPERTY(EditAnywhere)
	float RevealTime;

	UPROPERTY(EditAnywhere)
	bool AffectActors;

	UPROPERTY(EditAnywhere)
	TArray<class UNiagaraComponent*> FogComponents;

	TArray<TArray<class UNiagaraComponent*>> FogComponentsTable;

	UPROPERTY(VisibleAnywhere)
	TArray<FFogTimer> FogTimers;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* FogNiagaraSystem;

	UPROPERTY(EditAnywhere)
	FIntPoint Resolution;

	virtual void BeginPlay() override;

	void CheckActorsInFog();
	void UpdateFogTimers(float DeltaTime);

public:	

	FVector GetChunkSize();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static AFogOfWar* GetSingleton();

	FIntPoint LocationToIndex(FVector Location);

	virtual void Tick(float DeltaTime) override;

	void RevealChunks(TArray<FIntPoint> ChunksToReveal);
};
