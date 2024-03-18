#include "Report.h"

AReport::AReport()
{
	PrimaryActorTick.bCanEverTick = false;

	PaperMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paper Mesh Component"));
	PaperMeshComponent->SetSimulatePhysics(true);
	PaperMeshComponent->SetUseCCD(true);
	RootComponent = PaperMeshComponent;
}

void AReport::SetReportData_Implementation(const FUnitReport& ReportData)
{

}

void AReport::StartDragging()
{
	PaperMeshComponent->SetSimulatePhysics(false);
	SetActorEnableCollision(false);
}

void AReport::StopDragging()
{
	PaperMeshComponent->SetSimulatePhysics(true);
	SetActorEnableCollision(true);
}

FVector AReport::GetDragOffset()
{
	return FVector(0, 0, 5.f);
}
