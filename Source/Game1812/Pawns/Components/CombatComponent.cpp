#include "CombatComponent.h"

#include <Kismet/GameplayStatics.h>
#include "UnitMovementComponent.h"
#include "../CombatUnitStats.h"
#include "Damageable.h"
#include "../BaseUnit.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	UnitPawn = nullptr;
	TargetedEnemy = nullptr;

	HealthPoints = 0.f;
	Dead = false;
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	UnitPawn = Cast<ABaseUnit>(GetOwner());

	if (!UnitPawn)
		DestroyComponent();

}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Dead)
		return;

	FUnitOrder order = UnitPawn->GetCurrentOrder();

	UUnitMovementComponent* MovementComponent = UnitPawn->GetMovementComponent();

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
				if (FVector::DistSquared2D(TargetedEnemy->GetLocation(), UnitPawn->GetActorLocation()) < FMath::Pow(GetAttackRange(), 2))
				{
					MovementComponent->SetTargetLocation(UnitPawn->GetActorLocation());

					if (!MovementComponent->IsMoving())
					{
						Attack(TargetedEnemy, DeltaTime);
					}
				}
				else
				{
					MovementComponent->SetTargetLocation(TargetedEnemy->GetLocation());
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
	Target->ApplyDamage(this, FMath::Pow(1, 2) * GetBaseDamage() * HealthPoints * DeltaTime);
}

bool UCombatComponent::CanAttack(IDamageable* Target)
{
	const bool CloseEnoughToEnemy = FVector::DistSquared2D(TargetedEnemy->GetLocation(), UnitPawn->GetActorLocation()) < FMath::Pow(GetAttackRange(), 2);
	const bool Standing = !UnitPawn->GetMovementComponent()->IsMoving();

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
	return UnitPawn->GetCombatUnitStats().BaseDamage;
}

float UCombatComponent::GetAttackRange()
{
	return UnitPawn->GetCombatUnitStats().AttackDistance;
}

float UCombatComponent::GetDetectionRange()
{
	return UnitPawn->GetCombatUnitStats().EnemyDetectionRange;
}

void UCombatComponent::FindEnemiesInRange(TArray<IDamageable*>& OutArray)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UDamageable::StaticClass(), actors);

	for (AActor* actor : actors)
	{
		if (FVector::DistSquared2D(actor->GetActorLocation(), UnitPawn->GetActorLocation()) > FMath::Pow(GetDetectionRange(), 2))
			continue;

		IDamageable* damageable = Cast<IDamageable>(actor);

		if (!damageable)
			continue;

		if (!damageable->IsEnemy(UnitPawn->GetTeam()))
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
		if (FVector::DistSquared2D(damageable->GetLocation(), UnitPawn->GetActorLocation()) < FVector::DistSquared2D(closestDamageable->GetLocation(), UnitPawn->GetActorLocation()))
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
		UnitPawn->GetMovementComponent()->SetTargetLocation(TargetedEnemy->GetLocation());
	}
}

