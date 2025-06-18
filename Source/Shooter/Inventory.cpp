// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include <GameFramework/Actor.h>
#include "ShooterCharacter.h"
#include "Templates/SubclassOf.h"
// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventory::SetObjectIninventory(TSubclassOf<AActor> _object, int _index)
{
	objects[_index] = _object;
}

bool UInventory::HasAnEmptySlot()
{

	for (int i = 0; i < objects.Num(); i++)
	{
		if (objects[i] == nullptr)
		{
			return true;
		}
	}
	return false;
}

int UInventory::GetUIImageIndex(int _index)
{
//	if (GetObjectIninventory(_index) != nullptr)
//	{
//		if (Cast<AInventoryObjects>(objects[_index]->GetDefaultObject()) !=nullptr )
//		{
//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("fdfdf")));
//			AInventoryObjects* inventoryObject = Cast<AInventoryObjects>(GetObjectIninventory(_index).GetDefaultObject());
//			return inventoryObject->ImageUIIndex;
//		}
//		else
//		{
//			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("aze")));
//
//		}
//	}
//	
//
	return 0;
}

int UInventory::GetFreeSlot()
{
	int freeSlotIndex = -1;
	for (int i = 0; i < objects.Num(); i++)
	{
		if (objects[i] == nullptr)
		{
			freeSlotIndex = i;
			break;
		}
	}

	return freeSlotIndex;
}

class AShooterCharacter* UInventory::GetOwnerCharacter()
{
	return Cast<AShooterCharacter>(GetOwner());
}

