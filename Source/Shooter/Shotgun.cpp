// Fill out your copyright notice in the Description page of Project Settings.


#include "Shotgun.h"
#include <NiagaraComponent.h>

void AShotgun::Attack( AShooterCharacter* _character)
{
	if (waitToAttack == true)
	{
		return;
	}
	waitToAttack = true;
	if (bulletInMagazine > 0)
	{
		fireBurstFX->Activate(true);

		bulletInMagazine--;
		FVector spawnLoc = spawner->GetComponentLocation();
		TArray<FVector> BulletOffSet;
		BulletOffSet.SetNum(bulletToSpawn);
		for (int i = 0; i < bulletToSpawn; i++)
		{
			BulletOffSet[i] = FVector(FMath::RandRange(minBulletOffset,maxBulletOffset), FMath::RandRange(minBulletOffset, maxBulletOffset), FMath::RandRange(minBulletOffset, maxBulletOffset));
			SpawnBullet(_character, spawnLoc, BulletOffSet[i]);
		}
	}
	isFiring = true;
}

void AShotgun::StopAttack( AShooterCharacter* _character)
{
	Super::StopAttack(_character);
}