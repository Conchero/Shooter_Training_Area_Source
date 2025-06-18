// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WeaponBulletSave.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UWeaponBulletSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
		FString saveSlotName;
	UPROPERTY()
		FString nameExtension = "_BulletSave";
	UPROPERTY()
		int nbBullet = 3;
};
