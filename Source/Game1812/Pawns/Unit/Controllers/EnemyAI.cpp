#include "EnemyAI.h"

#include "EnemyUnitController.h"
#include "../Units/CombatUnit.h"
#include "../Orders/UnitOrder.h"

UCombatFormation::UCombatFormation()
{

}

void UCombatFormation::ValidateControllers()
{
	UnitControllers = UnitControllers.FilterByPredicate([](const TWeakObjectPtr<class AEnemyUnitController>& el) { return el.IsValid() && el->GetCombatUnit(); });
}

void UCombatFormation::MoveFormationTo(const FVector& Location, bool SkipValidation)
{
	if (!SkipValidation)
		ValidateControllers();

	AEnemyAI* ai = AEnemyAI::GetInstance();

	for (int i = 0; i < UnitControllers.Num(); i++)
	{
		UCombatUnitOrder* unitOrder = UnitControllers[i]->GetCombatUnit()->GetCombatUnitOrder();

		unitOrder->Location = Location + FVector(ai->GetFormationUnitOffset(UnitControllers.Num(), i), 50.f);
		
		UnitControllers[i]->GetCombatUnit()->AssignOrder(unitOrder);
	}
}

void UCombatFormation::AssembleFormation()
{
	ValidateControllers();

	if (UnitControllers.IsEmpty())
		return;

	FVector meanLocation = FVector::ZeroVector;

	for (TWeakObjectPtr<AEnemyUnitController> controller : UnitControllers)
	{
		meanLocation += controller->GetCombatUnit()->GetActorLocation();
	}

	meanLocation /= UnitControllers.Num();

	MoveFormationTo(meanLocation, true);
}

AEnemyAI* AEnemyAI::Instance = nullptr;

AEnemyAI::AEnemyAI()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1.f;

	CombatFormationsAmount = 3;
	AIState = EEnemyAIState::PreparingForBattle;

	FormationUnitOffsets = TArray<FFormationUnitOffset> {
		FFormationUnitOffset({ FVector2D(0.f, 0.f) }),
		FFormationUnitOffset({ FVector2D(0.f, -10.f), FVector2D(0.f, 10.f) }),
		FFormationUnitOffset({ FVector2D(0.f, -20.f), FVector2D(0.f, 0.f), FVector2D(0.f, 20.f) }),
		FFormationUnitOffset({ FVector2D(10.f, -10.f), FVector2D(10.f, 10.f), FVector2D(-10.f, -10.f), FVector2D(-10.f, 10.f) }),
		FFormationUnitOffset({ FVector2D(10.f, -20.f), FVector2D(10.f, 0.f), FVector2D(10.f, 20.f), FVector2D(-10.f, -10.f), FVector2D(-10.f, 10.f) }),
		FFormationUnitOffset({ FVector2D(10.f, -20.f), FVector2D(10.f, 0.f), FVector2D(10.f, 20.f), FVector2D(-10.f, -20.f), FVector2D(-10.f, 0.f), FVector2D(-10.f, 20.f) }),
		FFormationUnitOffset({ FVector2D(10.f, -30.f), FVector2D(10.f, -10.f), FVector2D(10.f, 10.f), FVector2D(10.f, 30.f), FVector2D(-10.f, -20.f), FVector2D(-10.f, 0.f), FVector2D(-10.f, 20.f) }),
		FFormationUnitOffset({ FVector2D(10.f, -30.f), FVector2D(10.f, -10.f), FVector2D(10.f, 10.f), FVector2D(10.f, 30.f),  FVector2D(-10.f, -30.f), FVector2D(-10.f, -10.f), FVector2D(-10.f, 10.f), FVector2D(-10.f, 30.f) }),
		FFormationUnitOffset({ FVector2D(20.f, -20.f), FVector2D(20.f, 0.f), FVector2D(20.f, 20.f), FVector2D(0.f, -20.f), FVector2D(0.f, 0.f), FVector2D(0.f, 20.f), FVector2D(-20.f, -20.f), FVector2D(-20.f, 0.f), FVector2D(-20.f, 20.f) }),
	};
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	Instance = this;

	CombatFormations.Empty();

	FTimerHandle handler;
	GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateUObject(this, &AEnemyAI::CreateFormationsTimeout));
}

void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AIState == EEnemyAIState::PreparingForBattle) 
	{
		if (CombatFormations.IsEmpty())
			return;

		for (UCombatFormation* formation : CombatFormations) 
		{
			formation->AssembleFormation();
		}

		AIState = EEnemyAIState::WaitingForAssembly;
	}
}

const FVector2D& AEnemyAI::GetFormationUnitOffset(int Amount, int Index) const
{
	if (Amount < 0 || Index < 0)
		return FVector2D::ZeroVector;

	if (Amount > FormationUnitOffsets.Num() - 1)
		Amount = FormationUnitOffsets.Num() - 1;

	if (Index > FormationUnitOffsets[Amount].UnitOffsets.Num() - 1) 
		return FVector2D::ZeroVector;

	return FormationUnitOffsets[Amount].UnitOffsets[Index];
}

void AEnemyAI::CreateFormationsTimeout()
{
	CreateFormations(AEnemyUnitController::GetEnemyControllers(), CombatFormationsAmount, 1000);
}

void AEnemyAI::CreateFormations(const TArray<AEnemyUnitController*>& Controllers, int FormationsAmount, int Iterations)
{
	if (FormationsAmount < 0)
		return;

	const static float RandomRange = 1500.f;

	//K-Means clustering

	TArray<FVector2D> clusterMeanPoints;
	clusterMeanPoints.SetNum(FormationsAmount);

	for (int i = 0; i < FormationsAmount; i++)
	{
		const float x = FMath::RandRange(-RandomRange, RandomRange);
		const float y = FMath::RandRange(-RandomRange, RandomRange);

		clusterMeanPoints[i] = FVector2D(x, y);
	}

	for (int iter = 0; iter < Iterations; iter++)
	{
		TArray<TArray<FVector2D>> relatedClusterPoints;
		relatedClusterPoints.SetNum(FormationsAmount);

		//Find close points
		for (AEnemyUnitController* controller : Controllers)
		{
			if (!controller->GetCombatUnit())
				continue;

			const FVector2D location = (FVector2D)controller->GetCombatUnit()->GetActorLocation();
			int minDistanceIndex = 0;
			float minDistance = UE_MAX_FLT;

			for (int i = 0; i < FormationsAmount; i++)
			{
				const float distance = FVector2D::DistSquared(location, clusterMeanPoints[i]);

				if (distance < minDistance)
				{
					minDistanceIndex = i;
					minDistance = distance;
				}
			}

			relatedClusterPoints[minDistanceIndex].Add(location);
		}


		//Apply means
		for (int i = 0; i < FormationsAmount; i++)
		{
			const TArray<FVector2D>& points = relatedClusterPoints[i];

			if (points.Num() == 0)
				continue;

			FVector2D pointMean;

			for (const FVector2D& point : points)
			{
				pointMean += point;
			}

			pointMean /= points.Num();
			clusterMeanPoints[i] = pointMean;
		}
	}

	CombatFormations.Empty();
	CombatFormations.SetNum(FormationsAmount);

	for (UCombatFormation*& formation : CombatFormations)
	{
		formation = NewObject<UCombatFormation>(this);
	}

	//Find cluster for formation
	for (AEnemyUnitController* controller : Controllers)
	{
		if (!controller->GetCombatUnit())
			continue;

		const FVector2D location = (FVector2D)controller->GetCombatUnit()->GetActorLocation();

		int minDistanceIndex = 0;
		float minDistance = UE_MAX_FLT;

		for (int i = 0; i < FormationsAmount; i++)
		{
			const float distance = FVector2D::DistSquared(location, clusterMeanPoints[i]);

			if (distance < minDistance)
			{
				minDistanceIndex = i;
				minDistance = distance;
			}
		}

		CombatFormations[minDistanceIndex]->UnitControllers.Add(controller);
		controller->SetCombatFormation(CombatFormations[minDistanceIndex]);
	}

	CombatFormations = CombatFormations.FilterByPredicate([](const UCombatFormation* el) { return !(el->UnitControllers.IsEmpty()); });
}


