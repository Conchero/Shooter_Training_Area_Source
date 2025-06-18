// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnZone.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnZone.generated.h"

UCLASS()
class SHOOTER_API AEnemySpawnZone : public ASpawnZone
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	FVector EnemyPos;
	UPROPERTY(EditAnywhere)
		TArray< TSubclassOf<class AEnemyCharacter> > enemyToSpawn;
		UFUNCTION(BlueprintImplementableEvent)
	void SpawnEnemy_BP();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy(int _nbToSpawn);
	virtual void Reset() override;

private:

};
