// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStats.h"
#include "ShooterCharacter.h"
// Sets default values for this component's properties
UCharacterStats::UCharacterStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterStats::BeginPlay()
{
	Super::BeginPlay();
	
	currentValue = maxValue;
	// ...

}


void UCharacterStats::SetNaturalRegen(float _v, bool _forced)
{
	if (_forced == false)
	{
		if (statNaturalRegen != 0 && statNaturalRegen > _v)
		{
			statNaturalRegen = _v;
		}
		else if (statNaturalRegen == 0)
		{
			statNaturalRegen = _v;
		}
	}
	else
	{
	    statNaturalRegen = _v;
	}

}

void UCharacterStats::NaturalDecay(float _dt)
{
	if (currentValue > 0)
	{
		currentValue -= _dt * statNaturalDecay;
	}
}

void UCharacterStats::RemoveValue(float _damage)
{
		currentValue -= _damage;
}

void UCharacterStats::NaturalRegeneration(float _dt)
{
	if (currentValue < maxValue)
	{
		currentValue += _dt * statNaturalRegen;
	}
	else if (currentValue >= maxValue)
	{
		statNaturalRegen = 0;
	}
}

void UCharacterStats::Heal(float _heal)
{
	if (currentValue + _heal > maxValue)
	{
		float unknownValue = ((int)currentValue + (int)_heal) - maxValue;
		float valueToAdd = (int)currentValue + (int)_heal - unknownValue;

		currentValue = valueToAdd;

	}
	else
	{
		currentValue += _heal;
	}

}

void UCharacterStats::PermanentDamage(float _damage)
{
	maxValue -= _damage;
	if (currentValue > maxValue)
	{
		currentValue = maxValue;
	}

}

float UCharacterStats::GetStatPercentage()
{
	return (currentValue / maxValue);
}

FString UCharacterStats::GetStatPoints()
{
	
	return FString::FromInt(static_cast<int>(currentValue)) + " / " + FString::FromInt(static_cast<int>(maxValue));
}

// Called every frame
void UCharacterStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	NaturalDecay(DeltaTime);

	NaturalRegeneration(DeltaTime);

	CheckZeroValue();
	// ...
}
//
//AActor* UCharacterStats::GetCharacter()
//{
//	return GetOwner();
//}

 void UCharacterStats::CheckZeroValue()
 {
	 if (currentValue < 0)
	 {
		 currentValue = 0;
	 }
 }

