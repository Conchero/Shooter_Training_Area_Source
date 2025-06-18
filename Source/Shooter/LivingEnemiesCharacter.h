// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "LivingEnemiesCharacter.generated.h"

/**
 *
 */

UCLASS()
class SHOOTER_API ALivingEnemiesCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:


	virtual void RemoveLife(float _v, TEnumAsByte<EWeaponElementType> _element) override;
protected:
	ALivingEnemiesCharacter();

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Health")
	class UHealthComponent* bloodHealth;
	UPROPERTY(EditAnywhere, Category = "Shield")
	class UShieldComponent* shieldHealth;

};
