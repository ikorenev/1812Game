#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FogOfWar.generated.h"

UCLASS()
class GAME1812_API AFogOfWar : public AActor
{
	GENERATED_BODY()
	
public:	

	AFogOfWar();

protected:

	UPROPERTY(EditAnywhere)
	TArray<class UNiagaraComponent*> FogComponents;

	TArray<TArray<class UNiagaraComponent*>> FogComponentsTable;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* FogNiagaraSystem;

	UPROPERTY(EditAnywhere)
	FVector2D Resolution;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
