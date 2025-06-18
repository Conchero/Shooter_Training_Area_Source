// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStats.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTER_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterStats();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "StatValue", BlueprintReadWrite)
		float maxValue = 100;
	UPROPERTY(EditAnywhere, Category = "StatValue", BlueprintReadWrite)
		float currentValue = 100;

	UPROPERTY(EditAnywhere, Category = "StatValue", BlueprintReadWrite)
		float statNaturalDecay;
	UPROPERTY(EditAnywhere, Category = "StatValue", BlueprintReadWrite)
		float statNaturalRegen;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetCurrentValue() { return currentValue; };
	void SetCurrentValue(float _v) { currentValue = _v; };
	float GetMaxValue() { return maxValue; };
	void SetMaxValue(float _v) {  maxValue = _v; };

	float GetNaturalDecay() { return statNaturalDecay; };
	void SetNaturalDecay(float _v) { statNaturalDecay = _v; };

	float GetNaturalRegen() { return statNaturalRegen; };
	void SetNaturalRegen(float _v, bool _forced);

	virtual void NaturalDecay(float _dt);
	void RemoveValue(float _damage);
	virtual void NaturalRegeneration(float _dt);
	void Heal(float _heal);
	void PermanentDamage(float _damage);
	UFUNCTION(BlueprintCallable)
		float GetStatPercentage();
	UFUNCTION(BlueprintCallable)
		FString GetStatPoints();

	//UFUNCTION(BlueprintCallable)
	//	class AActor* GetCharacter();
	float GetStatComsumption() { return maxValue - currentValue; };

	virtual void CheckZeroValue();
};
