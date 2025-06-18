// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryObjects.h"

// Sets default values
AInventoryObjects::AInventoryObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	objectMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObjectMesh");
	objectMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInventoryObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

