// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutomaticFirearm.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShotgun : public AAutomaticFirearm
{
	GENERATED_BODY()
public:
	virtual void Attack(class AShooterCharacter* _character) override;
	virtual void StopAttack(class AShooterCharacter* _character) override;

protected:
	UPROPERTY(EditAnywhere)
	int32 bulletToSpawn = 3;
};
