#include "Piece.h"

#include "../Pawns/Unit/UnitOrder.h"

#include "Kismet/GameplayStatics.h"
#include "../UI/BaseOrderWidget.h"
#include "../CossacksGameInstance.h"
#include "PaperMap.h"
#include <Components/BoxComponent.h>
#include "../Actors/HeadQuarters.h"
#include "../Pawns/Unit/CombatUnit.h"
#include <Components/StaticMeshComponent.h>
#include <Components/WidgetComponent.h>

APiece::APiece()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(FName("Piece Collision"));
	BoxCollisionComponent->InitBoxExtent(FVector(20, 20, 60));
	BoxCollisionComponent->SetGenerateOverlapEvents(true);
	RootComponent = BoxCollisionComponent;

	PieceFoundationMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piece Foundation"));
	PieceFoundationMeshComponent->SetupAttachment(BoxCollisionComponent);
	
	PieceFigureMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Piece Figure"));
	PieceFigureMeshComponent->SetupAttachment(BoxCollisionComponent);

	OrderWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("Order Widget"));
	OrderWidgetComponent->SetupAttachment(BoxCollisionComponent);
	OrderWidgetComponent->SetRelativeLocation(FVector(0, 0, 600));
	OrderWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	OrderWidgetComponent->SetDrawSize(FVector2D(200, 200));

	BoxCollisionComponent->SetSimulatePhysics(true);
	BoxCollisionComponent->SetNotifyRigidBodyCollision(true);

	bForceOrder = false;
}

void APiece::BeginPlay()
{
	Super::BeginPlay();

	BoxCollisionComponent->OnComponentHit.AddDynamic(this, &APiece::OnHit);
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APiece::OnBeginOverlap);
	BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &APiece::OnEndOverlap);

	OrderWidgetComponent->SetVisibility(false);

	UBaseOrderWidget* orderWidget = Cast<UBaseOrderWidget>(OrderWidgetComponent->GetWidget());

	if (!orderWidget) 
	{
		Destroy();
		return;
	}
		
	orderWidget->Init(this);
}

void APiece::SetCombatUnitType(ECombatUnitType NewCombatUnitType)
{
	CombatUnitType = NewCombatUnitType;

	auto gameInstance = GetGameInstance<UCossacksGameInstance>();

	if (!gameInstance)
		return;

	const FCombatUnitContainer& combatUnitContainer = gameInstance->GetTeamUnitsTable(ETeam::RUSSIA)->FindUnitStatsByType(CombatUnitType);

	PieceFoundationMeshComponent->SetStaticMesh(combatUnitContainer.PieceFoundationMesh);
	PieceFigureMeshComponent->SetStaticMesh(combatUnitContainer.PieceFigureMesh);
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

	if (bWasDragged) 
		RequestOrder();

	if (!Unit)
	{
		if (AHeadQuarters::GetInstance()) 
		{
			Unit = AHeadQuarters::GetInstance()->SpawnUnit(UnitClass);

			ACombatUnit* combatUnit = Cast<ACombatUnit>(Unit);

			if (combatUnit) 
			{
				combatUnit->SetCombatUnitType(CombatUnitType);
			}
		}
	}
}

void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void APiece::RequestOrder() 
{
	OrderWidgetComponent->SetVisibility(true);

	bWasDragged = false;
}

void APiece::RemoveOrder() 
{
	OrderWidgetComponent->SetVisibility(false);
}

void APiece::AssignOrder(FUnitOrder UnitOrder) 
{
	RemoveOrder();
	OnOrderAssign.Broadcast();

	if (!Unit) 
		return;

	if (bForceOrder) 
	{
		Unit->AssignOrder(UnitOrder);
	}
	else 
	{
		AHeadQuarters::GetInstance()->AddOrderToAssign(UnitOrder, Unit);
	}
}

void APiece::StartDragging()
{
	BoxCollisionComponent->SetSimulatePhysics(false);
	SetActorEnableCollision(false);

	FRotator rotation = GetActorRotation();
	rotation.Roll = 0.f;
	rotation.Pitch = 0.f;
	SetActorRotation(rotation);

	OnRemovedFromMap.Broadcast();

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


