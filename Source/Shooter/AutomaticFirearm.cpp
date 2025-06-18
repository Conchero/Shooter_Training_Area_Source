// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticFirearm.h"
#include "ShooterCharacter.h"

void AAutomaticFirearm::Attack(AShooterCharacter* _character)
{
	Super::Attack(_character);
	isFiring = true;
}

void AAutomaticFirearm::StopAttack(AShooterCharacter* _character)
{
	Super::StopAttack(_character);
	isFiring = false;
}

void AAutomaticFirearm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isFiring == true && waitToAttack == false)
	{
		Attack(GetCharacterOwner());
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("Fire")));

	}
}
