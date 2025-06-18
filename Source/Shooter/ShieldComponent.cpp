// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldComponent.h"
#include "EWeaponElementType.h"

UShieldComponent::UShieldComponent()
{
	elementalResistances[EWeaponElementType::NONE] = 1.f;
	elementalResistances[EWeaponElementType::FIRE] = 0.5f;
	elementalResistances[EWeaponElementType::ELECTRIC] = 1.5f;
	elementalResistances[EWeaponElementType::CORROSIVE] = 0.7;
}