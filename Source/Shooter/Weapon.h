// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryObjects.h"
#include "Weapon.generated.h"

UCLASS()
class SHOOTER_API AWeapon : public AInventoryObjects
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Stats")
	float damageDealt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Stats")
		float range;

	
    

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Stats")
		float coolDownAttack;
		float coolDownTimer;
		bool waitToAttack;
	UPROPERTY(EditAnywhere,Category = "Info")
	FString name;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Attack(class AShooterCharacter* _character);

	virtual void StopAttack(class AShooterCharacter* _character);

	float GetDamageDealt() { return damageDealt; };

	UFUNCTION(BlueprintCallable)
		float GetRange() { return range; };

};
