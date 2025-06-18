// Fill out your copyright notice in the Description page of Project Settings.


#include "LivingEnemiesCharacter.h"
#include "ShieldComponent.h"
#include "HealthComponent.h"


ALivingEnemiesCharacter::ALivingEnemiesCharacter()
{

	bloodHealth = CreateDefaultSubobject<UHealthComponent>(FName("blood health"));
	shieldHealth = CreateDefaultSubobject<UShieldComponent>(FName("shield health"));

	healths.SetNum(EHealthType::MAX_HEALTH);
	healths[mainHealth] = bloodHealth;
	healths[EHealthType::SHIELD] = shieldHealth;
}

void ALivingEnemiesCharacter::BeginPlay()
{
	Super::BeginPlay();
	healths.SetNum(EHealthType::MAX_HEALTH);
	healths[mainHealth] = bloodHealth;
	healths[EHealthType::SHIELD] = shieldHealth;
	if (shieldHealth == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%f"), 0.f));
	}
}



void ALivingEnemiesCharacter::RemoveLife(float _v, TEnumAsByte<EWeaponElementType> _element)
{
	//if (healths[EHealthType::SHIELD] != nullptr)
	//{
	//	if (healths[EHealthType::SHIELD]->GetCurrentValue() <= 0)
	//	{
	//		healths[EHealthType::BLOOD]->RemoveValue(_v);
	//		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%f"), 0.f));
	//	}
	//	else if (healths[EHealthType::SHIELD]->GetCurrentValue() >= 0)
	//	{
	//		healths[EHealthType::SHIELD]->RemoveValue(_v);
	//		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%f"), 1.f));
	//	}
	//}
	//else
	//{
	//	healths[EHealthType::BLOOD]->RemoveValue(_v);
	//}

	Super::RemoveLife(_v, _element);
}