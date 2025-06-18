// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnZone.h"
#include <Kismet/KismetMathLibrary.h>
#include <Components/BoxComponent.h>

// Sets default values
AEnemySpawnZone::AEnemySpawnZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawnZone::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy(numberToSpawn);
}

// Called every frame
void AEnemySpawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawnZone::SpawnEnemy(int _nbToSpawn)
{
//	EnemyPos.SetNum(_nbToSpawn);
	
	for (int i = 0; i < _nbToSpawn; i++)
	{
		int32 randBox = FMath::Rand() % triggerBoxes.Num();
		EnemyPos = triggerBoxes[randBox]->GetComponentLocation();
		int randEnemy = FMath::Rand() % enemyToSpawn.Num();
		if (enemyToSpawn[randEnemy] != nullptr)
		{
			AEnemyCharacter* enemy = GetWorld()->SpawnActor<AEnemyCharacter>(enemyToSpawn[randEnemy], EnemyPos, FRotator::ZeroRotator);
		}
	}

}

void AEnemySpawnZone::Reset()
{
	Super::Reset();


	//TArray<AActor*> dementedArray;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADemented::StaticClass(), dementedArray);
	//if (dementedArray.Num() > 0)
	//{
	//	for (auto demented : dementedArray)
	//	{
	//		if (demented != nullptr)
	//			demented->Destroy();
	//	}
	//}

	//SpawnDemented_BP();


}

