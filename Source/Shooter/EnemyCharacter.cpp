// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "ShieldComponent.h"
#include "HealthComponent.h"
#include <Components/WidgetComponent.h>
#include "ShooterCharacter.h"
#include <Kismet/KismetMathLibrary.h>
#include "Camera/CameraComponent.h"
#include "Firearm.h"
#include "ElementalComponent.h"
#include "Collectibles.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	boardMesh = CreateDefaultSubobject<UStaticMeshComponent>("boardMesh");
	boardMesh->SetupAttachment(RootComponent);
	healthBar = CreateDefaultSubobject<UWidgetComponent>("healthBar");
	healthBar->SetupAttachment(RootComponent);
	shieldBar = CreateDefaultSubobject<UWidgetComponent>("shieldBar");
	shieldBar->SetupAttachment(healthBar);

	effectsList.SetNum(EWeaponElementType::MAX_ELEMENT);
	effectsDuration.SetNum(EWeaponElementType::MAX_ELEMENT);
	effectsTickTimer.SetNum(EWeaponElementType::MAX_ELEMENT);
	effectsTick.SetNum(EWeaponElementType::MAX_ELEMENT);
	effectsDamage.SetNum(EWeaponElementType::MAX_ELEMENT);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//collectibleDropOnDeath.SetNum(EFirearmType::TYPE_COUNT);
	OnCharacterDeath.AddUniqueDynamic(this, &AEnemyCharacter::OnCharacterDeathManagement);

	if (healths[EHealthType::SHIELD] != nullptr)
	{

		if (healths[EHealthType::SHIELD] > 0)
		{
			currentConsumedHealth = EHealthType::SHIELD;
		}
		else
		{
			currentConsumedHealth = mainHealth;
		}
		OnShieldBroken.AddUniqueDynamic(this, &AEnemyCharacter::ShieldBrokeSwitchHealth);
	}

}



void AEnemyCharacter::SetEffects(int32 _index, AFirearm* _firearm)
{
	effectsList[_index] = true;
	effectsDuration[_index] = _firearm->GetElementalComponent()->elementalDuration;
	effectsTickTimer[_index] = _firearm->GetElementalComponent()->elementalTick;
	effectsTick[_index] = effectsTickTimer[_index];
	effectsDamage[_index] = _firearm->GetElementalComponent()->elementalDamage;
}

void AEnemyCharacter::ApplyEffects(int32 _index, float _dt, TEnumAsByte<EWeaponElementType> _element)
{
	effectsTickTimer[_index] -= _dt;
	if (effectsTickTimer[_index] <= 0)
	{
		//float elementalResistance = GetIndexHealth(currentConsumedHealth)->GetIndexElementalResistance(_index);
		RemoveLife(effectsDamage[_index], _element);
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%f"), elementalResistance));

		effectsTickTimer[_index] = effectsTick[_index];
	}

	effectsDuration[_index] -= _dt;

	if (effectsDuration[_index] <= 0)
	{
		effectsList[_index] = false;
	}
}


void AEnemyCharacter::OnBurn(AFirearm* _firearm)
{
	//effectsList[EWeaponElementType::FIRE] = true;
	//effectsDuration[EWeaponElementType::FIRE] = _firearm->GetElementalComponent()->elementalDuration;
	//effectsTick[EWeaponElementType::FIRE] = _firearm->GetElementalComponent()->elementalTick;
	//effectsDamage[EWeaponElementType::FIRE] = _firearm->GetElementalComponent()->elementalDamage;
}

void AEnemyCharacter::OnShock(AFirearm* _firearm)
{
//	effectsList[EWeaponElementType::ELECTRIC] = true;

}

void AEnemyCharacter::OnDisolve(AFirearm* _firearm)
{
	//effectsList[EWeaponElementType::CORROSIVE] = true;
}

void AEnemyCharacter::Burn(float _dt)
{


	//effectsTickTimer[EWeaponElementType::FIRE] -= _dt;
	//if (effectsTickTimer[EWeaponElementType::FIRE] <= 0)
	//{
	//	float elementalResistance = GetIndexHealth(currentConsumedHealth)->GetIndexElementalResistance(EWeaponElementType::FIRE);
	//	RemoveLife(effectsDamage[EWeaponElementType::FIRE] * elementalResistance);
	//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%f"), effectsDamage[EWeaponElementType::FIRE] * elementalResistance));

	//	effectsTickTimer[EWeaponElementType::FIRE] = effectsTick[EWeaponElementType::FIRE];
	//}

	//effectsDuration[EWeaponElementType::FIRE] -= _dt;

	//if (effectsDuration[EWeaponElementType::FIRE] <= 0)
	//{
	//	effectsList[EWeaponElementType::FIRE] = false;
	//}

	ApplyEffects(EWeaponElementType::FIRE, _dt, EWeaponElementType::FIRE);
}

void AEnemyCharacter::Shock(float _dt)
{
	ApplyEffects(EWeaponElementType::ELECTRIC, _dt, EWeaponElementType::ELECTRIC);

}

void AEnemyCharacter::Disolve(float _dt)
{
	ApplyEffects(EWeaponElementType::CORROSIVE, _dt, EWeaponElementType::CORROSIVE);

}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AShooterCharacter* character = Cast<AShooterCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (character != nullptr)
	{
		FVector lookAtPlayer = (character->GetFirstPersonCameraComponent()->GetForwardVector() * -1);

		if (healthBar != nullptr)
			healthBar->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(lookAtPlayer));
	}

	if (effectsList[EWeaponElementType::FIRE])
	{
		Burn(DeltaTime);
	}
	if (effectsList[EWeaponElementType::ELECTRIC])
	{
		Shock(DeltaTime);
	}
	if (effectsList[EWeaponElementType::CORROSIVE])
	{
		Disolve(DeltaTime);
	}
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyCharacter::GetAffectedByElement(TEnumAsByte<EWeaponElementType> _element, AFirearm* _firearm)
{
	TEnumAsByte<EWeaponElementType> element = _element;
	switch (_element)
	{
	case EWeaponElementType::FIRE:
		SetEffects(EWeaponElementType::FIRE, _firearm);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("OnFire")));
		break;
	case EWeaponElementType::ELECTRIC:
		SetEffects(EWeaponElementType::ELECTRIC, _firearm);
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("shocked")));
		break;
	case EWeaponElementType::CORROSIVE:
		SetEffects(EWeaponElementType::CORROSIVE, _firearm);
		break;
		default:
		break;
	}

}



void AEnemyCharacter::OnCharacterDeathManagement()
{
	int32 index = FMath::Rand() % collectibleDropOnDeath.Num();
	if (collectibleDropOnDeath[index] != nullptr)
	{
		GetWorld()->SpawnActor<ACollectibles>(collectibleDropOnDeath[index], GetActorLocation(), FRotator::ZeroRotator);
	}
	Destroy();
}

void AEnemyCharacter::ShieldBrokeSwitchHealth()
{
	currentConsumedHealth = mainHealth;
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("SwitchMade")));
}

void AEnemyCharacter::RemoveLife(float _v, TEnumAsByte<EWeaponElementType> _element)
{


	//if (healths[EHealthType::SHIELD] != nullptr)
	//{
	//	if (healths[EHealthType::SHIELD]->GetCurrentValue() <= 0)
	//	{
	//		healths[mainHealth]->RemoveValue(_v);
	//	}
	//	else if (healths[EHealthType::SHIELD]->GetCurrentValue() > 0)
	//	{
	//		healths[EHealthType::SHIELD]->RemoveValue(_v);
	//	}
	//}
	//else
	//{
	//	float elementalResistance = healths[mainHealth]->GetIndexElementalResistance(_element);
	//	healths[mainHealth]->RemoveValue(_v* elementalResistance);
	//}
	float elementalResistance = healths[currentConsumedHealth]->GetIndexElementalResistance(_element);
	float valueToRemove = _v * elementalResistance;

	if (healths[EHealthType::SHIELD] != nullptr)
	{
		if (healths[EHealthType::SHIELD]->GetCurrentValue() - valueToRemove <= 0)
		{
			if (currentConsumedHealth == EHealthType::SHIELD)
			{
				healths[EHealthType::SHIELD]->RemoveValue(valueToRemove);
				OnShieldBroken.Broadcast();
			}
		}
	}

	healths[currentConsumedHealth]->RemoveValue(valueToRemove);
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%f"), healths[currentConsumedHealth]->GetIndexElementalResistance(_element) ));

	if (healths[mainHealth]->GetCurrentValue() <= 0)
	{
		OnCharacterDeath.Broadcast();
	}
}
