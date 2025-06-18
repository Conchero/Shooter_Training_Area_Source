// Fill out your copyright notice in the Description page of Project Settings.


#include "MechanicEnemies.h"
#include "ArmorComponent.h"
#include "HealthComponent.h"
#include "ShieldComponent.h"

AMechanicEnemies::AMechanicEnemies()
{
	mainHealth = EHealthType::ARMOR;
	//healths[EHealthType::BLOOD] = CreateDefaultSubobject<UHealthComponent>("UHealthComponent");
	//healths[EHealthType::SHIELD] = CreateDefaultSubobject<UShieldComponent>("UShieldComponent");
	armorHealth = CreateDefaultSubobject<UArmorComponent>("armorHealth");
	shieldHealth = CreateDefaultSubobject<UShieldComponent>("shieldHealth");
	healths.SetNum(EHealthType::MAX_HEALTH);
	healths[mainHealth] =  armorHealth;
	healths[EHealthType::SHIELD] =  shieldHealth;
}

void AMechanicEnemies::RemoveLife(float _v, TEnumAsByte<EWeaponElementType> _element)
{

	Super::RemoveLife(_v, _element);
}

void AMechanicEnemies::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%d"), EHealthType::ARMOR));
	mainHealth = EHealthType::ARMOR;
	healths.SetNum(EHealthType::MAX_HEALTH);
	healths[mainHealth] = armorHealth;
	healths[EHealthType::SHIELD] = shieldHealth;
}
