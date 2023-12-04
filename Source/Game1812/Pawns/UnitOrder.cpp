#include "UnitOrder.h"

FUnitOrder::FUnitOrder()
{
	UnitEnemyReaction = EUnitEnemyReaction::ATTACK;

	bForcedMarch = false;
	bConcentratedFire = false;

	Location = FVector::ZeroVector;
	YawRotation = 0.f;
}

FUnitOrder::FUnitOrder(FVector Location, float YawRotation) : FUnitOrder()
{
	this->Location = Location;
	this->YawRotation = YawRotation;
}

bool FUnitOrder::IsSetToAttack()
{
	return UnitEnemyReaction == EUnitEnemyReaction::ATTACK;
}

bool FUnitOrder::IsSetToDefend()
{
	return UnitEnemyReaction == EUnitEnemyReaction::DEFEND;
}

