// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmunationBelt.h"
#include "EFirearmType.h"

// Sets default values for this component's properties
UAmmunationBelt::UAmmunationBelt()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ammunation.SetNum(EFirearmType::TYPE_COUNT);
	ammunation[EFirearmType::RIFLE] = 30;
	ammunation[EFirearmType::PISTOL] = 20;
	ammunation[EFirearmType::SHOTGUN] = 10;
	ammunation[EFirearmType::SNIPER] = 10;
}


// Called when the game starts
void UAmmunationBelt::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAmmunationBelt::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

