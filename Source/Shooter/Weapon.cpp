// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include <Engine/World.h>

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	coolDownTimer = coolDownAttack;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (waitToAttack == true)
	{
		coolDownTimer -= DeltaTime;
		if (coolDownTimer <= 0)
		{
			waitToAttack = false;
			coolDownTimer = coolDownAttack;
		}
	}

}

void AWeapon::Attack(class AShooterCharacter* _character)
{

}

void AWeapon::StopAttack(class AShooterCharacter* _character)
{

}



