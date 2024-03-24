#include "PieceMapMarker.h"

#include "Pieces/Piece.h"
#include "../CossacksGameInstance.h"

APieceMapMarker::APieceMapMarker()
{
	PrimaryActorTick.bCanEverTick = true;

	MarkerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Marker Mesh"));
	MarkerMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MarkerMeshComponent->SetWorldScale3D(FVector(0.1f));
	RootComponent = MarkerMeshComponent;

}

void APieceMapMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLocation();
	UpdateRotation();
}

void APieceMapMarker::OnPieceOrderAssign()
{
	Destroy();
}

void APieceMapMarker::UpdateLocation()
{
	if (!OwnerPiece)
		return;

	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(hit, OwnerPiece->GetActorLocation(), OwnerPiece->GetActorLocation() - FVector(0, 0, 4000.f), ECollisionChannel::ECC_GameTraceChannel1);

	SetActorLocation(hit.Location + FVector(0, 0, 10.f));
}

void APieceMapMarker::UpdateRotation()
{
	if (!OwnerPiece)
		return;

	SetActorRotation(OwnerPiece->GetResetRotation());
}

void APieceMapMarker::Init(APiece* NewOwnerPiece)
{
	if (!NewOwnerPiece)
		return;

	OwnerPiece = NewOwnerPiece;

	OwnerPiece->OnOrderAssign.AddDynamic(this, &APieceMapMarker::OnPieceOrderAssign);

	MarkerMeshComponent->SetStaticMesh(OwnerPiece->GetPieceFoundationMesh());

	UCossacksGameInstance* gameInstance = Cast<UCossacksGameInstance>(GetWorld()->GetGameInstance());
	if (gameInstance)
	{
		MarkerMeshComponent->SetMaterial(0, gameInstance->GetPieceMapMarkerMaterial());
	}

	UpdateLocation();
	UpdateRotation();
}