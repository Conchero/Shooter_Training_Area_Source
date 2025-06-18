// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "EWeaponElementType.h"

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), GetStatPercentage()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), GetStatPercentage()));
}

UHealthComponent::UHealthComponent()
{
	statNaturalDecay = 0;
	elementalResistances.SetNum(EWeaponElementType::MAX_ELEMENT);
	elementalResistances[EWeaponElementType::NONE] = 1.f;
	elementalResistances[EWeaponElementType::FIRE] = 1.5f;
	elementalResistances[EWeaponElementType::ELECTRIC] = 0.5f;
	elementalResistances[EWeaponElementType::CORROSIVE] = 0.7f;
}

UHealthComponent::~UHealthComponent()
{

}
