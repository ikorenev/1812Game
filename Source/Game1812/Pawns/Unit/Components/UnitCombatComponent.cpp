#include "UnitCombatComponent.h"

#include "UnitMovementComponent.h"
#include "Damageable.h"

#include "../CombatUnitDataAsset.h"
#include "../CombatUnit.h"
#include "../UnitOrder.h"

#include <Kismet/GameplayStatics.h>

UUnitCombatComponent::UUnitCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CombatUnitPawn = nullptr;
	TargetedEnemy = nullptr;

	HealthPoints = 0.f;
	Morale = 1.f;

	TimeOfLastAttack = -100.f;
}

void UUnitCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CombatUnitPawn = Cast<ACombatUnit>(GetOwner());

	if (!CombatUnitPawn)
		DestroyComponent();

	CombatUnitPawn->GetMovementComponent()->OnMove.AddDynamic(this, &UUnitCombatComponent::OnPawnMove);
}

void UUnitCombatComponent::Init(FCombatUnitStats* UnitCombatStats)
{
	if (!UnitCombatStats)
		return;

	HealthPoints = UnitCombatStats->GetBaseHP();
}

void UUnitCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UUnitMovementComponent* movementComponent = CombatUnitPawn->GetMovementComponent();

	if (!movementComponent->IsMoving()) 
	{
		const float moraleRestorationSpeed = CombatUnitPawn->GetCombatUnitStats()->GetMoraleRestorationSpeed();
		const float moraleRestoreDelta = moraleRestorationSpeed * DeltaTime;
		AddMorale(moraleRestoreDelta);
	}



	UCombatUnitOrder* order = Cast<UCombatUnitOrder>(CombatUnitPawn->GetCurrentOrder());

	if (!order)
		return;

	if (order->UnitEnemyReaction == EUnitEnemyReaction::Attack)
	{
		//Try to find enemy
		if (!TargetedEnemy.IsValid())
		{	
			IDamageable* enemy = FindClosestEnemyInRange();

			if (!enemy)
				return;

			SetTargetedEnemy(enemy);
		}
	}

	if (!TargetedEnemy.IsValid())
		return;

	//Walk to the enemy, if too far
	if (!IsTargetInRange(TargetedEnemy.Get()))
	{
		movementComponent->MoveTo(TargetedEnemy->GetLocation());
		return;
	}

	//Stop when enemy is close
	if (movementComponent->IsMoving())
		movementComponent->StopMoving();

	//TF2 soldier: ATTACK!
	TryAttack(TargetedEnemy.Get(), DeltaTime);
}

void UUnitCombatComponent::OnPawnMove(float Distance)
{
	const float moraleLoss = CombatUnitPawn->GetCombatUnitStats()->GetDistanceForFullMoraleLoss();

	if (moraleLoss != 0.f)
		AddMorale(-(Distance / moraleLoss));
}

void UUnitCombatComponent::OnBeingAttacked(IDamageable* Attacker)
{
	if (!TargetedEnemy.IsValid())
	{
		SetTargetedEnemy(Attacker);
		return;
	}

	if (!IsTargetInRange(TargetedEnemy.Get())) 
	{
		SetTargetedEnemy(Attacker);
	}
}

void UUnitCombatComponent::TryAttack(IDamageable* Target, float DeltaTime)
{
	if (CanAttack(Target))
	{
		Attack(Target, DeltaTime);

		TimeOfLastAttack = GetWorld()->GetTimeSeconds();
	}
}

void UUnitCombatComponent::Attack(IDamageable* Target, float DeltaTime)
{
	Target->ApplyDamage(CombatUnitPawn, CalculateDamage());
}

bool UUnitCombatComponent::CanAttack(IDamageable* Target)
{
	const bool closeEnoughToEnemy = IsTargetInRange(Target);
	const bool standing = !CombatUnitPawn->GetMovementComponent()->IsMoving();
	const bool cooldownFinished = GetAttackCooldown() + TimeOfLastAttack < GetWorld()->GetTimeSeconds();

	return closeEnoughToEnemy && standing && cooldownFinished;
}

bool UUnitCombatComponent::IsTargetInRange(IDamageable* Target)
{
	return FVector::DistSquared2D(Target->GetLocation(), CombatUnitPawn->GetActorLocation()) < FMath::Pow(GetAttackRange(), 2);
}

void UUnitCombatComponent::ApplyDamage(IDamageable* Attacker, float DamageAmount)
{
	HealthPoints -= FMath::Max(1, DamageAmount - CalculateDefense());

	if (HealthPoints < 0) 
	{
		CombatUnitPawn->Destroy();
		return;
	}

	if (Attacker)
		OnBeingAttacked(Attacker);
}

float UUnitCombatComponent::CalculateDamage()
{
	return FMath::Pow(Morale, 2) * GetBaseDamage() * HealthPoints;
}

float UUnitCombatComponent::CalculateDefense()
{
	return FMath::Pow(Morale, 2) * GetBaseDefense() * HealthPoints;
}

float UUnitCombatComponent::CalculateMovementSpeed()
{
	const float maxSpeed = CombatUnitPawn->GetCombatUnitStats()->GetMaxMovementSpeed();
	const float minSpeed = CombatUnitPawn->GetCombatUnitStats()->GetMinMovementSpeed();
	const float speed = Morale * (maxSpeed - minSpeed) + minSpeed;
	return FMath::Clamp(speed, minSpeed, maxSpeed);
}

void UUnitCombatComponent::FindEnemiesInRange(TArray<IDamageable*>& OutArray)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UDamageable::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		if (FVector::DistSquared2D(actor->GetActorLocation(), CombatUnitPawn->GetActorLocation()) > FMath::Pow(GetDetectionRange(), 2))
			continue;

		IDamageable* damageable = Cast<IDamageable>(actor);

		if (!damageable)
			continue;

		if (!damageable->IsEnemy(CombatUnitPawn->GetTeam()))
			continue;

		OutArray.Add(damageable);
	}
}

IDamageable* UUnitCombatComponent::FindClosestEnemyInRange()
{
	TArray<IDamageable*> damageables;

	FindEnemiesInRange(damageables);

	if (damageables.IsEmpty())
		return nullptr;

	IDamageable* closestDamageable = damageables[0];

	for (IDamageable* damageable : damageables)
	{
		if (FVector::DistSquared2D(damageable->GetLocation(), CombatUnitPawn->GetActorLocation()) < FVector::DistSquared2D(closestDamageable->GetLocation(), CombatUnitPawn->GetActorLocation()))
		{
			closestDamageable = damageable;
		}
	}

	return closestDamageable;
}

float UUnitCombatComponent::GetAttackCooldown()
{
	return CombatUnitPawn->GetCombatUnitStats()->GetAttackCooldown();
}

float UUnitCombatComponent::GetBaseDamage()
{
	return CombatUnitPawn->GetCombatUnitStats()->GetBaseDamage();
}

float UUnitCombatComponent::GetBaseDefense()
{
	return CombatUnitPawn->GetCombatUnitStats()->GetBaseDefense();
}

float UUnitCombatComponent::GetAttackRange()
{
	return CombatUnitPawn->GetCombatUnitStats()->GetAttackDistance();
}

float UUnitCombatComponent::GetDetectionRange()
{
	return CombatUnitPawn->GetCombatUnitStats()->GetEnemyDetectionRange();
}

void UUnitCombatComponent::AddMorale(float Amount)
{
	Morale = FMath::Clamp(Morale + Amount, 0.f, 1.f);
}

void UUnitCombatComponent::SetTargetedEnemy(IDamageable* NewTarget)
{
	TargetedEnemy = NewTarget;
}



