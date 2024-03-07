#include "UnitOrder.h"

UUnitOrder::UUnitOrder()
{
	

}

UCombatUnitOrder::UCombatUnitOrder()
{
	UnitEnemyReaction = EUnitEnemyReaction::ATTACK;

	bForcedMarch = false;
	bConcentratedFire = false;

	Location = FVector::ZeroVector;
	YawRotation = 0.f;
}

UScoutUnitOrder::UScoutUnitOrder()
{
	
}

UAdjutantUnitOrder::UAdjutantUnitOrder()
{

}


