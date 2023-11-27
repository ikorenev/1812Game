#include "UnitOrder.h"

FUnitOrder::FUnitOrder() 
{
	UnitEnemyReaction = EUnitEnemyReaction::ATTACK;

	bForcedMarch = false;
	bConcentratedFire = false;

	Location = FVector::ZeroVector;
	YawRotation = 0.f;
}