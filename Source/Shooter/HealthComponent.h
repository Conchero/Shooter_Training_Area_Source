// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats.h"
#include "HealthComponent.generated.h"

/**
 *
 */
UCLASS()
class SHOOTER_API UHealthComponent : public UCharacterStats
{
	GENERATED_BODY()
protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<float> elementalResistances;

public:

	UHealthComponent();
	~UHealthComponent();

	float GetIndexElementalResistance(int32 _index) { return elementalResistances[_index]; };

};
