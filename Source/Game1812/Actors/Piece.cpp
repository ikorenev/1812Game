#include "Piece.h"

#include "../Pawns/BaseUnit.h"
#include "PaperMap.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

APiece::APiece()
{
	PrimaryActorTick.bCanEverTick = true;

	PieceMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piece Mesh"));
	RootComponent = PieceMesh;

	OrderWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("Order Widget"));
	OrderWidgetComponent->SetupAttachment(RootComponent);
	OrderWidgetComponent->SetRelativeLocation(FVector(0, 0, 600));
	OrderWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	OrderWidgetComponent->SetDrawSize(FVector2D(200, 200));

	PieceMesh->SetSimulatePhysics(true);
	PieceMesh->SetNotifyRigidBodyCollision(true);

	HoverHeight = 10;
	SweepCastHeight = 200;
}

void APiece::BeginPlay()
{
	Super::BeginPlay();
	
	PieceMesh->OnComponentHit.AddDynamic(this, &APiece::OnHit);

	OrderWidgetComponent->SetVisibility(false);
}

void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector APiece::FindPointOnMap()
{
	FHitResult hit;

	GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), GetActorLocation() - FVector(0, 0, 1000), ECollisionChannel::ECC_GameTraceChannel1);

	if (!hit.bBlockingHit) return FVector(0);

	return hit.Location;
}

void APiece::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) return;

	APaperMap* map = Cast<APaperMap>(OtherActor);

	if (!map) return;

	if (Unit) 
	{
		Unit->MoveToLocation(FindPointOnMap());
	}
	else 
	{
		FVector point = FindPointOnMap();

		if (point.IsNearlyZero()) return;

		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Unit = GetWorld()->SpawnActor<ABaseUnit>(UnitClass.Get(), point, FRotator(0, GetActorRotation().Yaw, 0), spawnParams);
		
	}
}

void APiece::OnDragStart() 
{
	PieceMesh->SetSimulatePhysics(false);
	SetActorEnableCollision(false);
}

void APiece::OnDragEnd() 
{
	PieceMesh->SetSimulatePhysics(true);
	SetActorEnableCollision(true);
}

void APiece::OnMouseMove(FVector location, bool hover)
{
	FVector newLocation = FMath::VInterpTo(GetActorLocation(), hover ? location + FVector(0, 0, HoverHeight) : location, GetWorld()->GetDeltaSeconds(), 20);
	
	SetActorLocation(newLocation);
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), FRotator(0, GetActorRotation().Yaw, 0), GetWorld()->GetDeltaSeconds(), 20));
}

void APiece::OnRotate(float yawRotation) 
{
	AddActorWorldRotation(FRotator(0, yawRotation, 0));
}
