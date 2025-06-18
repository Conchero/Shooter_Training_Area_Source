// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Firearm.h"
#include "AutomaticFirearm.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AAutomaticFirearm : public AFirearm
{
	GENERATED_BODY()
public:
	virtual void Attack(class AShooterCharacter* _character) override;
	virtual void StopAttack(class AShooterCharacter* _character) override;

	virtual void Tick(float DeltaTime) override;
protected:
	bool isFiring;
};
