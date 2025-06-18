// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config = Game)
class AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Pawn mesh: 1st person view (arms; seen only by self) */
		UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

public:
	AShooterCharacter();
	virtual void Tick(float DeltaSeconds) override;
protected:
	virtual void BeginPlay();

	UPROPERTY(EditAnywhere)
		class UObjectInHandManager* objectInHandManager;

	UPROPERTY(EditAnywhere)
		class UInHandInventory* inHandInventory;

	UPROPERTY(EditAnywhere)
	class UAmmunationBelt* ammunationBelt;
	UFUNCTION(BlueprintImplementableEvent)
		void GetBackOnMainMenu_BP();
public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;


	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AShooterProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		UAnimMontage* FireAnimation;


	void SelectObject1();
	void SelectObject2();
	void SelectObject3();
	void SelectObject4();
	void ChangeObject(int32 _index);

	UFUNCTION(BlueprintCallable)
	class UAmmunationBelt* GetAmmunationBelt() {return ammunationBelt;};

	UFUNCTION(BlueprintCallable)
	int32 GetAmmunationToShow();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentWeaponAmmunation();

	UFUNCTION()
	void TryReload();

	void ShootRayCast();
	FHitResult shootRaycastHit;
	FHitResult GetShootRaycastHit() { return shootRaycastHit; };
	
	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);


protected:

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	UPROPERTY(EditAnywhere, Category = GroundPound)
		int32 groundPoundMultiplier = 1;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
	UFUNCTION(BlueprintCallable)
		void GroundPound(int32 _jumpLeft);


private:
	UFUNCTION(BlueprintCallable)
		virtual void MoveForwardAction(float Value);
	virtual void MoveRightAction(float Value);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION()
		void UseObjectInHand();
	void StopUseObjectInHand();
	UFUNCTION()
		void PlayFireAnimation();
};

