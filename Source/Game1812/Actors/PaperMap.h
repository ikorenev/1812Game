#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperMap.generated.h"

UCLASS()
class GAME1812_API APaperMap : public AActor
{
	GENERATED_BODY()
	
public:	

	APaperMap();

protected:

	UPROPERTY(EditAnywhere)
	float HideDistance;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MapMesh;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
