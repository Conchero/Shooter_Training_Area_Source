// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorComponent.h"
#include "EWeaponElementType.h"

UArmorComponent::UArmorComponent()
{
	elementalResistances[EWeaponElementType::NONE] = 1.f;
	elementalResistances[EWeaponElementType::FIRE] = 0.7f;
	elementalResistances[EWeaponElementType::ELECTRIC] = .7f;
	elementalResistances[EWeaponElementType::CORROSIVE] = 1.5f;
}