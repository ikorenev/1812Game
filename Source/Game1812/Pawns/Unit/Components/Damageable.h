#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../TeamEnum.h"
#include "Damageable.generated.h"


UINTERFACE()
class GAME1812_API UDamageable : public UInterface
{
    GENERATED_BODY()
};

class GAME1812_API IDamageable
{
    GENERATED_BODY()

public:

    virtual void ApplyDamage(class UCombatComponent* Attacker, float DamageAmount) {}

    virtual ETeam GetTeam() { return ETeam::RUSSIA; }
    virtual bool IsEnemy(ETeam Team) { return GetTeam() != Team; }

    virtual bool IsDead() { return false; }

    virtual FVector GetLocation() { return FVector::ZeroVector; }
};