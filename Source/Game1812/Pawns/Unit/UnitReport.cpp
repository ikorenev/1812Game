#include "UnitReport.h"

void FUnitReport::Clear()
{
	AlliedLosses = 0.f;
	EnemyLosses = 0.f;
	Morale.Empty();
}

float FUnitReport::GetAlliedLosses() const
{
	return AlliedLosses;
}

float FUnitReport::GetEnemyLosses() const
{
	return EnemyLosses;
}

float FUnitReport::GetAverageMorale() const
{
	if (Morale.Num() == 0)
		return 0.f;

	float sum = 0.f;

	for (float morale : Morale)
	{
		sum += morale;
	}

	return sum / Morale.Num();
}

void FUnitReport::AddAlliedLosses(float AddedAlliedLosses)
{
	AlliedLosses += AddedAlliedLosses;
}

void FUnitReport::AddEnemyLosses(float AddedEnemyLosses)
{
	EnemyLosses += AddedEnemyLosses;
}

void FUnitReport::SetMorale(float NewMorale)
{
	if (Morale.Num() != 0)
		Morale[0] = NewMorale;
}

FUnitReport& FUnitReport::operator+(const FUnitReport& Other)
{
	AlliedLosses += Other.AlliedLosses;
	EnemyLosses += Other.EnemyLosses;
	Morale.Append(Other.Morale);

	return *this;
}


