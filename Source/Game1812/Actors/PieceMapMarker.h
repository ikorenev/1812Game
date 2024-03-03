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
	UStaticMeshComponent* MarkerMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* MarkerMeshMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class APiece* OwnerPiece;

	virtual void BeginPlay() override;

	void OnPieceMapBorderStartOverlap();
	void OnPieceMapBorderEndOverlap();
	void OnOrderAssign();

	void UpdateLocation();

public:	

	void Init(class APiece* NewOwnerPiece);

	virtual void Tick(float DeltaTime) override;


};
