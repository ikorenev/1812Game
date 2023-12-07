#include "FogOfWar.h"

#include <Engine/Texture2D.h>
#include <NiagaraComponent.h>
#include <NiagaraFunctionLibrary.h>

AFogOfWar::AFogOfWar()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root Component"));

	Resolution = FVector2D(16, 16);
}

void AFogOfWar::BeginPlay()
{
	Super::BeginPlay();

	FogComponentsTable.SetNum(Resolution.X, true);

	for (int x = 0; x < Resolution.X; x++)
	{
		FogComponentsTable[x].SetNum(Resolution.Y, true);
	}

	for (int x = 0; x < Resolution.X; x++)
	{
		for (int y = 0; y < Resolution.Y; y++)
		{
			UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FogNiagaraSystem, RootComponent->GetComponentLocation() + FVector(x * 800 / Resolution.X, y * 800 / Resolution.Y, 0));

			FogComponents.Add(component);
			FogComponentsTable[x][y];
		}

	}
}

void AFogOfWar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

