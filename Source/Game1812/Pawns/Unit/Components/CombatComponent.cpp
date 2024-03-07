#include "CombatComponent.h"

#include "UnitMovementComponent.h"
#include "Damageable.h"

#include "../CombatUnitStats.h"
#include "../CombatUnit.h"

#include <Kismet/GameplayStatics.h>

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	CombatUnitPawn = nullptr;
	TargetedEnemy = nullptr;

	HealthPoints = 0.f;
	Dead = false;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	CombatUnitPawn = Cast<ACombatUnit>(GetOwner());

	if (!CombatUnitPawn)
		DestroyComponent();

}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Dead)
		return;

	FUnitOrder order = CombatUnitPawn->GetCurrentOrder();

	UUnitMovementComponent* MovementComponent = CombatUnitPawn->GetMovementComponent();

	if (order.IsSetToAttack())
	{
		if (TargetedEnemy)
		{
			if (TargetedEnemy->IsDead()) 
			{
				SetTargetedEnemy(nullptr);
			}
			else
			{
				if (FVector::DistSquared2D(TargetedEnemy->GetLocation(), CombatUnitPawn->GetActorLocation()) < FMath::Pow(GetAttackRange(), 2))
				{
					MovementComponent->MoveTo(CombatUnitPawn->GetActorLocation());

					if (!MovementComponent->IsMoving())
					{
						Attack(TargetedEnemy, DeltaTime);
					}
				}
				else
				{
					MovementComponent->MoveTo(TargetedEnemy->GetLocation());
				}
			}
		}
		else 
		{
			IDamageable* enemy = FindClosestEnemyInRange();

			if (enemy) 
			{
				SetTargetedEnemy(enemy);
			}
		}
	}

}

void UCombatComponent::Init(FCombatUnitStats UnitCombatStats)
{
	HealthPoints = UnitCombatStats.StartHP;
}

void UCombatComponent::TryAttack(IDamageable* Target, float DeltaTime)
{
	if (CanAttack(Target))
	{
		Attack(Target, DeltaTime);
	}
}

void UCombatComponent::Attack(IDamageable* Target, float DeltaTime)
{
	//TODO: Боевой дух
	Target->ApplyDamage(this, FMath::Pow(1.0f, 2) * GetBaseDamage() * HealthPoints * DeltaTime);
}

bool UCombatComponent::CanAttack(IDamageable* Target)
{
	const bool CloseEnoughToEnemy = FVector::DistSquared2D(TargetedEnemy->GetLocation(), CombatUnitPawn->GetActorLocation()) < FMath::Pow(GetAttackRange(), 2);
	const bool Standing = !CombatUnitPawn->GetMovementComponent()->IsMoving();

	return CloseEnoughToEnemy && Standing;
}

void UCombatComponent::ApplyDamage(UCombatComponent* Attacker, float DamageAmount)
{
	HealthPoints -= DamageAmount;

	if (HealthPoints < 0) 
	{
		Dead = true;
	}
}

float UCombatComponent::GetBaseDamage()
{
	return CombatUnitPawn->GetUnitStats().BaseDamage;
}

float UCombatComponent::GetAttackRange()
{
	return CombatUnitPawn->GetUnitStats().AttackDistance;
}

float UCombatComponent::GetDetectionRange()
{
	return CombatUnitPawn->GetUnitStats().EnemyDetectionRange;
}

bool UCombatComponent::IsDead()
{
	return Dead;
}

void UCombatComponent::FindEnemiesInRange(TArray<IDamageable*>& OutArray)
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

		if (damageable->IsDead())
			continue;

		OutArray.Add(damageable);
	}
}

IDamageable* UCombatComponent::FindClosestEnemyInRange()
{
	TArray<IDamageable*> damageables;

	FindEnemiesInRange(damageables);

	if (damageables.IsEmpty()) return nullptr;

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

void UCombatComponent::SetTargetedEnemy(IDamageable* NewTarget)
{
	TargetedEnemy = NewTarget;
	
	if (TargetedEnemy) 
	{
		CombatUnitPawn->GetMovementComponent()->MoveTo(TargetedEnemy->GetLocation());
	}
}

