#include "FogOfWar.h"

#include <Components/BoxComponent.h>
#include <NiagaraComponent.h>
#include <NiagaraFunctionLibrary.h>
#include <Kismet/GameplayStatics.h>

FFogTimer::FFogTimer()
{
	FogComponent = nullptr;
	Timer = 0.f;
}

FFogTimer::FFogTimer(const FFogTimer& Other)
{
	FogComponent = Other.FogComponent;
	Timer = Other.Timer;
}

FFogTimer::FFogTimer(UNiagaraComponent* FogComponent, float Timer)
{
	this->FogComponent = FogComponent;
	this->Timer = Timer;
}

bool operator==(const FFogTimer& First, const FFogTimer& Second)
{
	return First.FogComponent == Second.FogComponent;
}



AFogOfWar* AFogOfWar::Singleton = nullptr;

AFogOfWar* AFogOfWar::GetSingleton()
{
	return Singleton;
}

AFogOfWar::AFogOfWar()
{
	PrimaryActorTick.bCanEverTick = true;

	FogArea = CreateDefaultSubobject<UBoxComponent>(FName("Fog Area"));
	FogArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = FogArea;

	Resolution = FIntPoint(20, 20);
	 
	RevealTime = 15.f;

	HideAffectedActors = true;
}

void AFogOfWar::BeginPlay()
{
	Super::BeginPlay();

	Singleton = this;

	if (!FogNiagaraSystem) return;

	FogComponentsTable.SetNum(Resolution.X, true);

	for (int x = 0; x < Resolution.X; x++)
	{
		FogComponentsTable[x].SetNum(Resolution.Y, true);
	}
	
	
	const FVector FogBoxExtent = FogArea->GetScaledBoxExtent() * 2;
	const FVector SystemSize = GetChunkSize();

	for (int x = 0; x < Resolution.X; x++)
	{
		for (int y = 0; y < Resolution.Y; y++)
		{
			UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FogNiagaraSystem, RootComponent->GetComponentLocation() + FVector(x * FogBoxExtent.X / Resolution.X, y * FogBoxExtent.Y / Resolution.Y, 0) - FVector(FogArea->GetScaledBoxExtent().X, FogArea->GetScaledBoxExtent().Y, 0));

			component->SetVectorParameter("Size", SystemSize);

			FogComponents.Add(component);
			FogComponentsTable[x][y] = component;
		}
	}
}


void AFogOfWar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFogTimers(DeltaTime);

	if (HideAffectedActors)
	{
		CheckActorsInFog();
	}
}

void AFogOfWar::CheckActorsInFog()
{
	TArray<AActor*> affectedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "AffectedByFog", affectedActors);

	for (AActor* actor : affectedActors)
	{
		if (!actor)
			continue;

		FIntPoint index = LocationToIndex(actor->GetActorLocation());

		if (FogComponentsTable[index.X][index.Y]->ComponentTags.Contains("Hidden"))
		{
			actor->SetActorHiddenInGame(false);
		}
		else
		{
			actor->SetActorHiddenInGame(true);
		}
	}
}

void AFogOfWar::UpdateFogTimers(float DeltaTime)
{
	for (int i = 0; i < FogTimers.Num();) 
	{
		FogTimers[i].Timer -= DeltaTime;

		if (FogTimers[i].Timer <= 0)
		{
			FogTimers[i].FogComponent->SetNiagaraVariableFloat("SpawnRate", 1.0f);
			FogTimers[i].FogComponent->ComponentTags.Remove("Hidden");
			FogTimers.RemoveAt(i);
		}
		else 
		{
			i++;
		}
	}
}

void AFogOfWar::RevealChunks(TArray<FIntPoint> ChunksToReveal)
{
	for (FIntPoint chunk : ChunksToReveal) 
	{
		UNiagaraComponent* component = FogComponentsTable[chunk.X][chunk.Y];

		FFogTimer* fogTimer = FogTimers.FindByPredicate([&](const FFogTimer& el) { return el.FogComponent == component; });

		if (fogTimer)
		{
			fogTimer->Timer = RevealTime;
		}
		else 
		{
			FogTimers.Add(FFogTimer(component, RevealTime));
			component->SetNiagaraVariableFloat("SpawnRate", 0.0f);
			component->ComponentTags.Add("Hidden");
		}
	}
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


