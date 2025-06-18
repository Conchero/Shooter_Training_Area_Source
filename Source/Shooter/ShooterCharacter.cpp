// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterCharacter.h"
#include "ShooterProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include <GameFramework/CharacterMovementComponent.h>
#include <DrawDebugHelpers.h>
#include <Components/BoxComponent.h>
#include "JumpableWallComponent.h"
#include "WallJumpComponent.h"
#include "ObjectInHandManager.h"
#include "InHandInventory.h"
#include "Weapon.h"
#include "AmmunationBelt.h"
#include "EFirearmType.h"
#include "Firearm.h"
#include "WeaponBulletSave.h"
#include "ShooterGameMode.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AShooterCharacter

AShooterCharacter::AShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	//// Create a gun mesh component
	//FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	//FP_Gun->bCastDynamicShadow = false;
	//FP_Gun->CastShadow = false;
	//// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);



	objectInHandManager = CreateDefaultSubobject<UObjectInHandManager>(TEXT("objectInHandManager"));
	inHandInventory = CreateDefaultSubobject<UInHandInventory>(TEXT("inHandInventory"));
	ammunationBelt = CreateDefaultSubobject<UAmmunationBelt>(TEXT("ammunationBelt"));

	JumpMaxCount = 2;
}

void AShooterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (Cast<AShooterGameMode>(GetWorld()->GetAuthGameMode()) != nullptr)
	{
		AShooterGameMode* gameMode = Cast<AShooterGameMode>(GetWorld()->GetAuthGameMode());
		gameMode->secondTimer -= DeltaSeconds;
		if (gameMode->secondTimer <= 0)
		{
			if (gameMode->minutesTimer <= 0)
			{
				GetBackOnMainMenu_BP();
				return;
			}
			gameMode->secondTimer = gameMode->secondValue;
			gameMode->minutesTimer--;

		}
	}
}

void AShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}




//////////////////////////////////////////////////////////////////////////
// Input

void AShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterCharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AShooterCharacter::Sprint);
	//PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AShooterCharacter::UnSprint);

	// Bind fire event
	PlayerInputComponent->BindAction("SelectObject1", IE_Pressed, this, &AShooterCharacter::SelectObject1);
	PlayerInputComponent->BindAction("SelectObject2", IE_Pressed, this, &AShooterCharacter::SelectObject2);
	PlayerInputComponent->BindAction("SelectObject3", IE_Pressed, this, &AShooterCharacter::SelectObject3);
	PlayerInputComponent->BindAction("SelectObject4", IE_Pressed, this, &AShooterCharacter::SelectObject4);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AShooterCharacter::TryReload);
	PlayerInputComponent->BindAction("UseObject", IE_Pressed, this, &AShooterCharacter::UseObjectInHand);
	PlayerInputComponent->BindAction("UseObject", IE_Released, this, &AShooterCharacter::StopUseObjectInHand);
	//PlayerInputComponent->BindAction("GetCrouched", IE_Pressed, this, &AShooterCharacter::GetCrouched);

	// Enable touchscreen input
	//EnableTouchscreenMovement(PlayerInputComponent);

	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AShooterCharacter::OnResetVR);

	// Bind movement events
	//PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);
}


void AShooterCharacter::SelectObject1()
{
	ChangeObject(0);
}

void AShooterCharacter::SelectObject2()
{
	ChangeObject(1);
}

void AShooterCharacter::SelectObject3()
{
	ChangeObject(2);
}

void AShooterCharacter::SelectObject4()
{
	ChangeObject(3);
}

void AShooterCharacter::ChangeObject(int32 _index)
{
	objectInHandManager->GetBareHand();
	int index = _index;
	inHandInventory->SetSlotSelected(index);
	if (inHandInventory->GetObjectIninventory(index) != nullptr)
	{
		objectInHandManager->SpawnObjectInHand(inHandInventory->GetObjectIninventory(index));
	}
	else
	{
		objectInHandManager->GetBareHand();
	}
}

int32 AShooterCharacter::GetAmmunationToShow()
{
	if (objectInHandManager != nullptr)
	{
		if (objectInHandManager->GetObjectSpawned() != nullptr)
		{
			if (Cast<AFirearm>(objectInHandManager->GetObjectSpawned()) != nullptr)
			{
				AFirearm* firearm = Cast<AFirearm>(objectInHandManager->GetObjectSpawned());
				return GetAmmunationBelt()->GetIndexAmmunation(firearm->GetFirearmType());
			}
		}
	}

	return 0;
}

int32 AShooterCharacter::GetCurrentWeaponAmmunation()
{
	if (objectInHandManager != nullptr)
	{
		if (objectInHandManager->GetObjectSpawned() != nullptr)
		{
			if (Cast<AFirearm>(objectInHandManager->GetObjectSpawned()) != nullptr)
			{
				AFirearm* firearm = Cast<AFirearm>(objectInHandManager->GetObjectSpawned());
				return firearm->GetBulletInMagazine();
			}
		}
	}
	return 0;
}

void AShooterCharacter::TryReload()
{
	if (objectInHandManager != nullptr)
	{
		if (objectInHandManager->GetObjectSpawned() != nullptr)
		{
			if (Cast<AFirearm>(objectInHandManager->GetObjectSpawned()) != nullptr)
			{
				AFirearm* firearm = Cast<AFirearm>(objectInHandManager->GetObjectSpawned());
				firearm->Reload(this);
			}
		}
	}
}

void AShooterCharacter::ShootRayCast()
{
	FVector raycastStart = FirstPersonCameraComponent->GetComponentLocation();
	FVector raycastEnd = raycastStart + (FirstPersonCameraComponent->GetForwardVector() * 10000000);

	DrawDebugLine(GetWorld(), raycastStart, raycastEnd, FColor::Magenta, true);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(shootRaycastHit, raycastStart, raycastEnd, ECollisionChannel::ECC_Visibility, Params);

}

//void AShooterCharacter::Save()
//{
//	if (UWeaponBulletSave* SaveGameObject = Cast<UWeaponBulletSave>(UGameplayStatics::CreateSaveGameObject(UWeaponBulletSave::StaticClass())))
//	{
//		SaveGameObject->nbBullet = 50;
//
//		FAsyncSaveGameToSlotDelegate asyncSave;
//		asyncSave.BindUObject(this, &AShooterCharacter::SaveAction);
//		UGameplayStatics::AsyncSaveGameToSlot(SaveGameObject, "nana", 0, asyncSave);
//	}
//}
//
//void AShooterCharacter::SaveAction(const FString& slotName, const int32 UserIndex, bool sucess)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("done")));
//
//}
//
//void AShooterCharacter::Load()
//{
//	if (UWeaponBulletSave* SaveGameObject = Cast<UWeaponBulletSave>(UGameplayStatics::CreateSaveGameObject(UWeaponBulletSave::StaticClass())))
//	{
//		FAsyncLoadGameFromSlotDelegate asyncLoad;
//		asyncLoad.BindUObject(this, &AShooterCharacter::LoadAction);
//
//		UGameplayStatics::AsyncLoadGameFromSlot("nana", 0, asyncLoad);
//	}
//}
//
//void AShooterCharacter::LoadAction(const FString& slotName, const int32 UserIndex, class USaveGame* loadedGameData)
//{
//	if (UWeaponBulletSave* SaveGameTemp = Cast<UWeaponBulletSave>(loadedGameData))
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("%d"), SaveGameTemp->nbBullet));
//	}
//}

void AShooterCharacter::GroundPound(int32 _jumpLeft)
{
	if (_jumpLeft <= 0)
	{
		FVector startLocation = GetActorLocation() + (GetActorUpVector() * (-40));
		FVector endLocation = startLocation + (GetActorUpVector() * (-1000));
		FHitResult hitResult;
		GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility);

		//DrawDebugLine(GetWorld(), startLocation, endLocation,FColor::Red,true);
		if (hitResult.bBlockingHit == true)
		{
			FVector velocityGroundPound = hitResult.ImpactPoint - GetActorLocation();
			LaunchCharacter(velocityGroundPound * groundPoundMultiplier, true, true);
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("%f,%f,%f"), velocityGroundPound.X, velocityGroundPound.Y, velocityGroundPound.Z));
		}
	}
}


void AShooterCharacter::UseObjectInHand()
{
	if (objectInHandManager != nullptr)
	{
		if (objectInHandManager->GetObjectSpawned() != nullptr)
		{
			if (Cast<AWeapon>(objectInHandManager->GetObjectSpawned()) != nullptr)
			{
				AWeapon* weapon = Cast<AWeapon>(objectInHandManager->GetObjectSpawned());
				weapon->Attack(this);
			}
		}
	}
}


void AShooterCharacter::StopUseObjectInHand()
{
	if (objectInHandManager != nullptr)
	{
		if (objectInHandManager->GetObjectSpawned() != nullptr)
		{
			if (Cast<AWeapon>(objectInHandManager->GetObjectSpawned()) != nullptr)
			{
				AWeapon* weapon = Cast<AWeapon>(objectInHandManager->GetObjectSpawned());
				weapon->StopAttack(this);
			}
		}
	}
}



void AShooterCharacter::PlayFireAnimation()
{
	if (FireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}



void AShooterCharacter::MoveForward(float Value)
{
	MoveForwardAction(Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	MoveRightAction(Value);
}

void AShooterCharacter::MoveForwardAction(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AShooterCharacter::MoveRightAction(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void AShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

