// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryObjects.h"
#include "Weapon.h"
#include "EFireArmType.h"
#include "Firearm.generated.h"

/**
 *
 */

UCLASS()
class SHOOTER_API AFirearm : public AWeapon
{
	GENERATED_BODY()
public:
	AFirearm();

	virtual void Attack(class AShooterCharacter* _character) override;
	virtual void StopAttack(class AShooterCharacter* _character) override;
	virtual void Reload(AShooterCharacter* _character);

	UFUNCTION(BlueprintCallable)
		float GetBreakageChange() { return breakageChance; };

	UFUNCTION(BlueprintCallable)
		float GetFirebackStrenght() { return firebackStrenght; };

	UFUNCTION(BlueprintCallable)
		int32 GetMagazineCapacity() { return magazineCapacity; };

	UFUNCTION(BlueprintCallable)
		int32 GetBulletInMagazine() { return bulletInMagazine; };

	UFUNCTION(BlueprintCallable)
		TEnumAsByte<EFirearmType> GetFirearmType() { return type; };

	void SaveBulletInMagazine();
	void SaveBulletInMagazine_Action(const FString& slotName, const int32 UserIndex, bool sucess);
	void LoadBulletInMagazine();
	void LoadBulletInMagazine_Action(const FString& slotName, const int32 UserIndex,class USaveGame* loadedGameData);
	UFUNCTION(BlueprintCallable)
	class UElementalComponent* GetElementalComponent() { return elementComponent; };
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		float breakageChance;
	UPROPERTY(EditAnywhere)
		float firebackStrenght = -0.5f;

	UPROPERTY(EditAnywhere)
		int32 magazineCapacity = 10;
		int32 bulletInMagazine;

	UPROPERTY(EditAnywhere)
		class USceneComponent* spawner;

	UPROPERTY(EditAnywhere)
    float minBulletOffset;
	UPROPERTY(EditAnywhere)
    float maxBulletOffset;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> bulletReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector launchDir;

	UFUNCTION(BlueprintImplementableEvent)
	void SetLaunchDir_BP();

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EFirearmType> type;
	UPROPERTY(EditAnywhere)
    class UElementalComponent* elementComponent;
	void SpawnBullet(AShooterCharacter* _character,FVector _location, FVector _velocityOffset);

	virtual void Destroy(bool bNetForce /* = false */, bool bShouldModifyLevel /* = true */) ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UNiagaraComponent* fireBurstFX;
};
