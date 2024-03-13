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
	bIsTemporarilyDefeated = false;

	TimeOfLastAttack = -100.f;
	TimeOfLastTakenDamage = -100.f;
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

	UpdateMoraleRestoration(DeltaTime);

	if (bIsTemporarilyDefeated) 
	{
		if (Morale > 0.5f) 
		{
			bIsTemporarilyDefeated = false;
			return;
		}

		

		return;
	}

	UpdateOrderBehaviour();

	UpdateTargetAttack();
}

void UUnitCombatComponent::UpdateMoraleRestoration(float DeltaTime)
{
	if (CombatUnitPawn->GetMovementComponent()->IsMoving() || (TimeOfLastTakenDamage + 5.f > GetWorld()->GetTimeSeconds()))
		return;

	const float moraleRestorationSpeed = CombatUnitPawn->GetCombatUnitStats()->GetMoraleRestorationSpeed();
	const float moraleRestoreDelta = moraleRestorationSpeed * DeltaTime;
	AddMorale(moraleRestoreDelta);
}

void UUnitCombatComponent::UpdateOrderBehaviour()
{
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
}

void UUnitCombatComponent::UpdateTargetAttack()
{
	UUnitMovementComponent* movementComponent = CombatUnitPawn->GetMovementComponent();

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
	TryAttack(TargetedEnemy.Get());
}

void UUnitCombatComponent::OnPawnMove(float Distance)
{
	const float moraleLoss = CombatUnitPawn->GetCombatUnitStats()->GetDistanceForFullMoraleLoss();

	if (moraleLoss != 0.f)
		AddMorale(-(Distance / moraleLoss));
}

void UUnitCombatComponent::OnBeingAttackedBehaviour(IDamageable* Attacker)
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

void UUnitCombatComponent::TryAttack(IDamageable* Target)
{
	if (CanAttack(Target))
	{
		Attack(Target);

		TimeOfLastAttack = GetWorld()->GetTimeSeconds();
	}
}

void UUnitCombatComponent::Attack(IDamageable* Target)
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
	const float totalDamage = FMath::Max(1, DamageAmount - CalculateDefense());
	HealthPoints -= totalDamage;

	if (HealthPoints < 0)
	{
		CombatUnitPawn->Destroy();
		return;
	}

	const float moraleLoss = CombatUnitPawn->GetCombatUnitStats()->GetMoraleLossDueToLosses();
	AddMorale(-(totalDamage * moraleLoss));

	if (Morale < 0.05f) 
	{
		bIsTemporarilyDefeated = true;

	}

	TimeOfLastTakenDamage = GetWorld()->GetTimeSeconds();

	if (Attacker)
		OnBeingAttackedBehaviour(Attacker);
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

FVector UUnitCombatComponent::FindRetreatDirection()
{
	TArray<IDamageable*> enemies;

	FindEnemiesInRange(enemies);

	
}

float UUnitCombatComponent::GetAttackCooldown() const
{
	return CombatUnitPawn->GetCombatUnitStats()->GetAttackCooldown();
}

float UUnitCombatComponent::GetBaseDamage() const
{
	return CombatUnitPawn->GetCombatUnitStats()->GetBaseDamage();
}

float UUnitCombatComponent::GetBaseDefense() const
{
	return CombatUnitPawn->GetCombatUnitStats()->GetBaseDefense();
}

float UUnitCombatComponent::GetAttackRange() const
{
	return CombatUnitPawn->GetCombatUnitStats()->GetAttackDistance();
}

float UUnitCombatComponent::GetDetectionRange() const
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



