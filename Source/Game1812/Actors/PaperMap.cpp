#include "PaperMap.h"

#include "../Pawns/PlayerPawn.h"
#include "../Pawns/Components/PlayerMovementComponent.h"
#include "../Pawns/Components/CameraArmComponent.h"


APaperMap::APaperMap()
{
	PrimaryActorTick.bCanEverTick = true;

	MapMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Map Mesh"));
	RootComponent = MapMesh;

	MapMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	HideDistance = 150;
}

void APaperMap::BeginPlay()
{
	Super::BeginPlay();
	
	


}

void APaperMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!pawn) return;

	APlayerPawn* playerPawn = Cast<APlayerPawn>(pawn);

	if (!playerPawn) return;

	if ((playerPawn->GetMovementComponent()->GetMapState() == EPlayerCameraState::LookingAtMap) && 
		(playerPawn->GetCameraArmComponent()->GetCurrentLength() < HideDistance)) 
	{
		MapMesh->SetVisibility(false);
	}
	else 
	{
		MapMesh->SetVisibility(true);
	}
}

