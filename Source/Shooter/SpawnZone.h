// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnZone.generated.h"

UCLASS()
class SHOOTER_API ASpawnZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* triggerBox1;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* triggerBox2;
		UPROPERTY(EditAnywhere)
		class UBoxComponent* triggerBox3;
		UPROPERTY(EditAnywhere)
			class UBoxComponent* triggerBox4;
		UPROPERTY(EditAnywhere)
		TArray<class UBoxComponent*> triggerBoxes;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
		int numberToSpawn = 5;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
   void Reset();
};
