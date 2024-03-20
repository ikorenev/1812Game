#include "UnitPathArrow.h"

#include <Components/SplineComponent.h>
#include <Components/SplineMeshComponent.h>

AUnitPathArrow::AUnitPathArrow()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	SplinePathComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Path Component"));
	SplinePathComponent->SetupAttachment(RootComponent);

	SegmentLength = 100.0f;
}

void AUnitPathArrow::OnConstruction(const FTransform& Transform)
{
	BuildArrow();
}

void AUnitPathArrow::BeginPlay()
{
	Super::BeginPlay();

}

void AUnitPathArrow::BuildArrow()
{
	const float splineLength = SplinePathComponent->GetSplineLength();
	const int amountOfSegments = (int)(splineLength / SegmentLength);

	for (int i = 0; i < amountOfSegments + 1; i++) 
	{
		USplineMeshComponent* splineMeshComponent = NewObject<USplineMeshComponent>(this);

		if (i == 0) 
		{
			splineMeshComponent->SetStaticMesh(ArrowOutlineEndStaticMesh);
		}
		else if (i == amountOfSegments) 
		{
			splineMeshComponent->SetStaticMesh(ArrowOutlineStartStaticMesh);
		}
		else 
		{
			splineMeshComponent->SetStaticMesh(ArrowOutlineMiddleStaticMesh);
		}
		
		splineMeshComponent->SetMobility(EComponentMobility::Stationary);
		splineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		splineMeshComponent->RegisterComponentWithWorld(GetWorld());
		splineMeshComponent->AttachToComponent(SplinePathComponent, FAttachmentTransformRules::KeepRelativeTransform);
		splineMeshComponent->SetForwardAxis(ESplineMeshAxis::X);
	
		const FVector startPoint = SplinePathComponent->GetLocationAtDistanceAlongSpline(SegmentLength * i, ESplineCoordinateSpace::Local);
		const FVector startTangent = SplinePathComponent->GetTangentAtDistanceAlongSpline(SegmentLength * i, ESplineCoordinateSpace::Local);
		const FVector endPoint = SplinePathComponent->GetLocationAtDistanceAlongSpline(SegmentLength * (i + 1), ESplineCoordinateSpace::Local);
		const FVector endTangent = SplinePathComponent->GetTangentAtDistanceAlongSpline(SegmentLength * (i + 1), ESplineCoordinateSpace::Local);

		const FVector adjustedStartTangent = startTangent.GetSafeNormal() * SegmentLength;
		const FVector adjustedEndTangent = endTangent.GetSafeNormal() * SegmentLength;

		splineMeshComponent->SetStartAndEnd(startPoint, adjustedStartTangent, endPoint, adjustedEndTangent, true);
		
		splineMeshComponent->SetStartScale(FVector2D(1, 1));
		splineMeshComponent->SetEndScale(FVector2D(1, 1));
	}
}

void AUnitPathArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

