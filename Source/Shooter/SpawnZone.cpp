// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnZone.h"

// Sets default values
ASpawnZone::ASpawnZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	triggerBox1 = CreateDefaultSubobject<UBoxComponent>("triggerBox1");
	triggerBox1->SetupAttachment(RootComponent);
	triggerBox2 = CreateDefaultSubobject<UBoxComponent>("triggerBox2");
	triggerBox2->SetupAttachment(RootComponent);
	triggerBox3 = CreateDefaultSubobject<UBoxComponent>("triggerBox3");
	triggerBox3->SetupAttachment(RootComponent);
	triggerBox4 = CreateDefaultSubobject<UBoxComponent>("triggerBox4");
	triggerBox4->SetupAttachment(RootComponent);

	triggerBoxes.Add(triggerBox1);
	triggerBoxes.Add(triggerBox2);
	triggerBoxes.Add(triggerBox3);
	triggerBoxes.Add(triggerBox4);
}

// Called when the game starts or when spawned
void ASpawnZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnZone::Reset()
{

}

