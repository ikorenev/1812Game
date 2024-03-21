#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitPathArrow.generated.h"

UCLASS()
class GAME1812_API AUnitPathArrow : public AActor
{
	GENERATED_BODY()
	
public:	

	AUnitPathArrow();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USplineComponent* SplinePathComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class USplineMeshComponent*> SplineMeshComponents;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* ArrowOutlineStartStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* ArrowOutlineMiddleStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* ArrowOutlineEndStaticMesh;

	UPROPERTY()
	class UNavigationPath* Path;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SegmentLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ArrowLocationHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector EndPoint;

	virtual void BeginPlay() override;

	void BuildArrow();

	void UpdatePath();

	void UpdateSplineWithPath();

	FVector ProjectPointToMap(const FVector& Point);

public:	

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

	void SetEndPoint(const FVector& NewEndPoint);

};
