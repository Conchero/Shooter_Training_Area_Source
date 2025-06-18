// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EWeaponElementType.h"
#include "ElementalComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UElementalComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UElementalComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<EWeaponElementType> weaponElement;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere)
		float elementalDamage;
	UPROPERTY(EditAnywhere)
		float elementalDuration;
	UPROPERTY(EditAnywhere)
		float elementalTick;
	UPROPERTY(EditAnywhere)
		float elementalChance;
	UFUNCTION(BlueprintCallable)
	TEnumAsByte<EWeaponElementType> GetWeaponElement() { return weaponElement; };
};
