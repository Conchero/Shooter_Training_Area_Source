// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmunationBelt.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UAmmunationBelt : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAmmunationBelt();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	 TArray<int32> ammunation;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetIndexAmmunation(int32 _index) { return ammunation[_index];};
	void SetIndexAmmunation(int32 _index,int32 _v) { ammunation[_index] = _v; };
	void RemoveIndexAmmunation(int32 _index,int32 _v) { ammunation[_index] -= _v; };
		
};
