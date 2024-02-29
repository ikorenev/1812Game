#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PieceMapMarker.generated.h"

UCLASS()
class GAME1812_API APieceMapMarker : public AActor
{
	GENERATED_BODY()
	
public:	

	APieceMapMarker();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MapMarkerMeshComponent;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
