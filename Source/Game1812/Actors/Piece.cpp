#include "Piece.h"

#include "../Pawns/Unit/UnitOrder.h"
#include "../Pawns/Unit/CombatUnit.h"
#include "../UI/BaseOrderWidget.h"
#include "../CossacksGameInstance.h"
#include "HeadQuarters.h"
#include "PieceMapMarker.h"
#include "PaperMap.h"

#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

APiece::APiece()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(FName("Piece Collision"));
	BoxCollisionComponent->InitBoxExtent(FVector(20, 20, 60));
	BoxCollisionComponent->SetSimulatePhysics(true);
	BoxCollisionComponent->SetNotifyRigidBodyCollision(true);
	BoxCollisionComponent->SetGenerateOverlapEvents(true);
	RootComponent = BoxCollisionComponent;

	PieceFoundationMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piece Foundation"));
	PieceFoundationMeshComponent->SetupAttachment(BoxCollisionComponent);
	
	PieceFigureMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piece Figure"));
	PieceFigureMeshComponent->SetupAttachment(BoxCollisionComponent);

	OrderWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("Order Widget"));
	OrderWidgetComponent->SetRelativeLocation(FVector(0, 0, 600));
	OrderWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	OrderWidgetComponent->SetDrawSize(FVector2D(400, 400));
	OrderWidgetComponent->SetupAttachment(BoxCollisionComponent);
	
	bCanSpawnUnit = true;
	bWasDragged = false;
	bIsDead = false;
}

void APiece::BeginPlay()
{
	Super::BeginPlay();

	BoxCollisionComponent->OnComponentHit.AddDynamic(this, &APiece::OnHit);

	OrderWidgetComponent->SetVisibility(false);

	UBaseOrderWidget* orderWidget = Cast<UBaseOrderWidget>(OrderWidgetComponent->GetWidget());

	if (!orderWidget) 
	{
		Destroy();
		return;
	}
		
	orderWidget->Init(this);
}

void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APiece::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) 
		return;

	APaperMap* map = Cast<APaperMap>(OtherActor);

	if (!map) 
		return;

	HitComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
	HitComponent->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);

	if (bIsDead)
		return;

	if (bWasDragged)
	{
		RequestOrder();

		SpawnMapMarker();
		
		bWasDragged = false;
	}
	
	if (!bCanSpawnUnit)
		return;
	
	SpawnUnit();
	bCanSpawnUnit = false;
}

void APiece::RequestOrder() 
{
	OrderWidgetComponent->SetVisibility(true);
}

void APiece::RemoveOrder() 
{
	OrderWidgetComponent->SetVisibility(false);
}

void APiece::SpawnUnit()
{
	if (!AHeadQuarters::GetInstance())
		return;
	
	Unit = AHeadQuarters::GetInstance()->SpawnUnit(UnitClass);
	Unit->SetOwnerPiece(this);
}

void APiece::SpawnMapMarker()
{
	if (MapMarker.IsValid())
		return;

	MapMarker = GetWorld()->SpawnActor<APieceMapMarker>();
	MapMarker->Init(this);
}

void APiece::AssignOrder(UUnitOrder* UnitOrder)
{
	RemoveOrder();

	OnOrderAssign.Broadcast();
}

FRotator APiece::GetResetRotation()
{
	FRotator rotation = GetActorRotation();
	rotation.Roll = 0.f;
	rotation.Pitch = 0.f;
	return rotation;
}

void APiece::ResetRotation()
{
	SetActorRotation(GetResetRotation());
}

UStaticMesh* APiece::GetPieceFoundationMesh()
{
	return PieceFoundationMeshComponent->GetStaticMesh();
}

void APiece::SetUnitDead()
{
	bIsDead = true;

	RemoveOrder();

	PieceFoundationMeshComponent->SetMaterial(0, MaterialOnDeath);
	PieceFigureMeshComponent->SetMaterial(0, MaterialOnDeath);
}

void APiece::StartDragging()
{
	BoxCollisionComponent->SetSimulatePhysics(false);
	SetActorEnableCollision(false);

	ResetRotation();
	RemoveOrder();
}

void APiece::StopDragging()
{
	BoxCollisionComponent->SetSimulatePhysics(true);
	SetActorEnableCollision(true);

	bWasDragged = true;
}

FVector APiece::GetDragOffset()
{
	return FVector(0, 0, BoxCollisionComponent->GetScaledBoxExtent().Z);
}

