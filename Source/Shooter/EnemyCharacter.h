// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EWeaponElementType.h"
#include "EHealthType.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDeathDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShieldBrokenDelegate);

UCLASS()
class SHOOTER_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	FCharacterDeathDelegate OnCharacterDeath;


	UFUNCTION()
	void OnCharacterDeathManagement();

	FOnShieldBrokenDelegate OnShieldBroken;

	UFUNCTION()
		void ShieldBrokeSwitchHealth();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<class UHealthComponent*> healths;
	
	UPROPERTY(EditAnywhere)
    TArray<TSubclassOf<class ACollectibles>> collectibleDropOnDeath;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* boardMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UWidgetComponent* healthBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* shieldBar;

	TArray<bool> effectsList;
	TArray<float> effectsDuration;
	TArray<float> effectsTickTimer;
	TArray<float> effectsTick;
	TArray<float> effectsDamage;

	TEnumAsByte<EHealthType> mainHealth = EHealthType::BLOOD;
	TEnumAsByte<EHealthType> currentConsumedHealth;

	void SetEffects(int32 _index, class AFirearm* _firearm);
	void ApplyEffects(int32 _index, float _dt, TEnumAsByte<EWeaponElementType> _element);

	UFUNCTION()
	void OnBurn(class AFirearm* _firearm);
	UFUNCTION()
		void OnShock(class AFirearm* _firearm);
	UFUNCTION()
		void OnDisolve(class AFirearm* _firearm);

	UFUNCTION()
		void Burn(float _dt);
	UFUNCTION()
		void Shock(float _dt);
	UFUNCTION()
		void Disolve(float _dt);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void RemoveLife(float _v, TEnumAsByte<EWeaponElementType> _element);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable)
	class UHealthComponent* GetIndexHealth(int32 _index) { return healths[_index]; };

	void GetAffectedByElement(TEnumAsByte<EWeaponElementType> _element, class AFirearm* _firearm);
	TEnumAsByte<EHealthType> GetCurrentHealth() { return currentConsumedHealth; };
	
};
