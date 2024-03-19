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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USplineComponent* SplinePathComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* ArrowOutlineStartStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* ArrowOutlineMiddleStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* ArrowOutlineEndStaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float SegmentLength;

	

	virtual void BeginPlay() override;

	void BuildArrow();

public:	

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void Tick(float DeltaTime) override;

};
