// Fill out your copyright notice in the Description page of Project Settings.


#include "Firearm.h"
#include "Bullet.h"
#include <Components/SceneComponent.h>
#include <Kismet/KismetMathLibrary.h>
#include "ShooterCharacter.h"
#include "AmmunationBelt.h"
#include "WeaponBulletSave.h"
#include <Kismet/GameplayStatics.h>
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "ElementalComponent.h"
#include <../Plugins/FX/Niagara/Source/Niagara/Public/NiagaraComponent.h>

AFirearm::AFirearm()
{
	spawner = CreateDefaultSubobject<USceneComponent>(FName("Spawner"));
	spawner->SetupAttachment(objectMesh);
	fireBurstFX = CreateDefaultSubobject<UNiagaraComponent>(FName("fireBurstFX"));
	fireBurstFX->SetupAttachment(spawner);
	fireBurstFX->Deactivate();
	fireBurstFX->bAutoActivate = false;
	range = 100.f;
	elementComponent = CreateDefaultSubobject<UElementalComponent>(FName("elementComponent"));
}

void AFirearm::Attack(AShooterCharacter* _character)
{
	Super::Attack(_character);
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
		FVector bulletOffset = FVector(FMath::RandRange(minBulletOffset,maxBulletOffset), FMath::RandRange(minBulletOffset, maxBulletOffset), FMath::RandRange(minBulletOffset, maxBulletOffset));
		SpawnBullet(_character, spawnLoc, bulletOffset);
	}
}

void AFirearm::StopAttack(class AShooterCharacter* _character)
{
	Super::StopAttack(_character);
}

void AFirearm::Reload(AShooterCharacter* _character)
{
	int32 nbBulletsToReload = magazineCapacity - bulletInMagazine;

	int32 nbToTakeFromAmmunitions = nbBulletsToReload - _character->GetAmmunationBelt()->GetIndexAmmunation(type);
	if (nbBulletsToReload <= _character->GetAmmunationBelt()->GetIndexAmmunation(type))
	{
		bulletInMagazine += nbBulletsToReload;
		_character->GetAmmunationBelt()->RemoveIndexAmmunation(type, nbBulletsToReload);
	}
	else if (nbBulletsToReload > _character->GetAmmunationBelt()->GetIndexAmmunation(type))
	{
		bulletInMagazine += _character->GetAmmunationBelt()->GetIndexAmmunation(type);
		_character->GetAmmunationBelt()->RemoveIndexAmmunation(type, _character->GetAmmunationBelt()->GetIndexAmmunation(type));
	}
}

void AFirearm::BeginPlay()
{
	Super::BeginPlay();
	bulletInMagazine = magazineCapacity;
	LoadBulletInMagazine();
}


void AFirearm::SaveBulletInMagazine()
{
	if (UWeaponBulletSave* SaveGameObject = Cast<UWeaponBulletSave>(UGameplayStatics::CreateSaveGameObject(UWeaponBulletSave::StaticClass())))
	{
		FString slotName = name + SaveGameObject->nameExtension;
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, slotName);

		SaveGameObject->nbBullet = bulletInMagazine;
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%d"), SaveGameObject->nbBullet));
		FAsyncSaveGameToSlotDelegate asyncSave;
		asyncSave.BindUObject(this, &AFirearm::SaveBulletInMagazine_Action);
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, slotName, 0, asyncSave);
	}
}

void AFirearm::SaveBulletInMagazine_Action(const FString& slotName, const int32 UserIndex, bool sucess)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("done")));

}

void AFirearm::LoadBulletInMagazine()
{
	if (UWeaponBulletSave* SaveGameObject = Cast<UWeaponBulletSave>(UGameplayStatics::CreateSaveGameObject(UWeaponBulletSave::StaticClass())))
	{
		FString slotName = name + SaveGameObject->nameExtension;
		if (UGameplayStatics::DoesSaveGameExist(slotName, 0) == true)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, slotName);
			FAsyncLoadGameFromSlotDelegate asyncLoad;
			asyncLoad.BindUObject(this, &AFirearm::LoadBulletInMagazine_Action);
			UGameplayStatics::AsyncLoadGameFromSlot(slotName, 0, asyncLoad);
		}
	}
}

void AFirearm::LoadBulletInMagazine_Action(const FString& slotName, const int32 UserIndex, USaveGame* loadedGameData)
{
	if (UWeaponBulletSave* SaveGameTemp = Cast<UWeaponBulletSave>(loadedGameData))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%d"),SaveGameTemp->nbBullet));
		bulletInMagazine = SaveGameTemp->nbBullet;
	}
}

void AFirearm::SpawnBullet(AShooterCharacter* _character,FVector _location, FVector _velocityOffset)
{
	
		if (bulletReference != nullptr && spawner != nullptr)
		{
			_character->LookUpAtRate(firebackStrenght);
			FVector crossHairVector = FVector::ZeroVector;
			if (GetCharacterOwner() != nullptr)
			{
				GetCharacterOwner()->ShootRayCast();
				if (GetCharacterOwner()->GetShootRaycastHit().bBlockingHit)
				{
					crossHairVector = GetCharacterOwner()->GetShootRaycastHit().ImpactPoint;
					launchDir = crossHairVector;
				}
				else
				{
					crossHairVector = GetCharacterOwner()->GetShootRaycastHit().TraceEnd;
					launchDir = crossHairVector;
				}
			}
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%d"), 0));

			//ABullet* bulletSpawned = GetWorld()->SpawnActor<ABullet>(bulletReference, spawner->GetComponentLocation(), forwardRotation);
			ABullet* bulletSpawned = GetWorld()->SpawnActorDeferred<ABullet>(bulletReference, this->GetTransform());
			FRotator forwardRotation = UKismetMathLibrary::FindLookAtRotation(spawner->GetComponentLocation(), launchDir + _velocityOffset);
			bulletSpawned->SetActorLocation(_location);
			bulletSpawned->SetActorRotation(forwardRotation);
			bulletSpawned->SetSpawner(this);
			bulletSpawned->FinishSpawning(this->GetTransform());
			_character->PlayFireAnimation();
		}
	

}

void AFirearm::Destroy(bool bNetForce /* = false */, bool bShouldModifyLevel /* = true */)
{
	//SaveBulletInMagazine();
	//FString toprint = "passedincheck";
	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, toprint);
	Super::Destroy(bNetForce, bShouldModifyLevel);
}