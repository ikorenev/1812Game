#include "PieceMapMarker.h"

#include "Piece.h"

APieceMapMarker::APieceMapMarker()
{
	PrimaryActorTick.bCanEverTick = true;

	MarkerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker Mesh"));
	MarkerMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MarkerMeshComponent;
}

void APieceMapMarker::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateLocation();
}

void APieceMapMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APieceMapMarker::OnPieceMapBorderStartOverlap()
{
	MarkerMeshComponent->SetVisibility(true);
}

void APieceMapMarker::OnPieceMapBorderEndOverlap()
{
	MarkerMeshComponent->SetVisibility(false);
}

void APieceMapMarker::OnOrderAssign()
{
	Destroy();
}

void APieceMapMarker::UpdateLocation()
{
	if (!OwnerPiece)
		return;

	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(hit, OwnerPiece->GetActorLocation(), OwnerPiece->GetActorLocation() - FVector(0, 0, 2000.f), ECollisionChannel::ECC_GameTraceChannel1);

	SetActorLocation(hit.Location - FVector(0, 0, 10.f));
}

void APieceMapMarker::Init(APiece* NewOwnerPiece)
{
	if (!NewOwnerPiece)
		return;

	OwnerPiece = NewOwnerPiece;

	OwnerPiece->OnMapBordersStartOverlap.AddUObject(this, &APieceMapMarker::OnPieceMapBorderStartOverlap);
	OwnerPiece->OnMapBordersEndOverlap.AddUObject(this, &APieceMapMarker::OnPieceMapBorderEndOverlap);
	OwnerPiece->OnOrderAssign.AddUObject(this, &APieceMapMarker::OnOrderAssign);

	MarkerMeshComponent->SetStaticMesh(OwnerPiece->GetPieceFoundationMesh());

	UpdateLocation();
}