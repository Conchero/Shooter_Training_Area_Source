// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "MechanicEnemies.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AMechanicEnemies : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	AMechanicEnemies();

	virtual void RemoveLife(float _v, TEnumAsByte<EWeaponElementType> _element) override;

	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
		class UArmorComponent* armorHealth;
	UPROPERTY(EditAnywhere)
		class UShieldComponent* shieldHealth;
};
