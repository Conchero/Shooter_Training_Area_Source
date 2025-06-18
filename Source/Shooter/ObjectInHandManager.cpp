// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectInHandManager.h"
#include "ShooterCharacter.h"
#include "Firearm.h"
//#include "InventoryObjects.h"
//#include "../Weapons/Weapon.h"

// Sets default values for this component's properties
UObjectInHandManager::UObjectInHandManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectInHandManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UObjectInHandManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectInHandManager::SpawnObjectInHand(TSubclassOf<class AActor> _objectToSpawn)
{
	if (object == nullptr)
	{
		object = _objectToSpawn;
		//USkeletalMeshComponent* skeletalMesh = GetSkeletalMesh();
		//FVector SpawnLoc = skeletalMesh->GetSocketTransform(FName("UsableObjectSocket"), ERelativeTransformSpace::RTS_World).GetLocation();
		objectSpawned = GetOwner()->GetWorld()->SpawnActor<AActor>(object, GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
		if (objectSpawned != nullptr)
		{
			AttachToPawn();

			AInventoryObjects* inventoryObject = Cast<AInventoryObjects>(objectSpawned);

			if (inventoryObject != nullptr)
			{
					inventoryObject->SetCharacterOwner(Cast<AShooterCharacter>(GetOwner()));
				objectSpawned->SetActorRelativeRotation(inventoryObject->GetRotation());
				objectSpawned->SetActorRelativeLocation(inventoryObject->GetOffset());
			}
		}
	}
}



void UObjectInHandManager::GetBareHand()
{
	if (object != nullptr)
	{
		object = nullptr;
	}
	if (objectSpawned != nullptr)
	{
		CheckFirearm(objectSpawned);
		objectSpawned->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		objectSpawned->Destroy();
		objectSpawned = nullptr;
	}

}
void UObjectInHandManager::CheckFirearm(AActor* _objectToCheck)
{
	if (_objectToCheck != nullptr)
	{
		if (Cast<AFirearm>(_objectToCheck))
		{
			AFirearm* firearm = Cast<AFirearm>(_objectToCheck);
			firearm->SaveBulletInMagazine();
			FString toprint = "passedincheck";
			//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, toprint);
		}
	}
}


void UObjectInHandManager::AttachToPawn()
{
	//USkeletalMeshComponent* skeletalMesh = GetSkeletalMesh();
	//FAttachmentTransformRules tranformRules = FAttachmentTransformRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//tranformRules.LocationRule = EAttachmentRule::SnapToTarget;
	//tranformRules.RotationRule = EAttachmentRule::SnapToTarget;
	//tranformRules.ScaleRule = EAttachmentRule::SnapToTarget;
	//tranformRules.bWeldSimulatedBodies = false;
	AShooterCharacter* ownerCharacter = nullptr;
	if (Cast<AShooterCharacter>(GetOwner()) != nullptr)
		ownerCharacter = Cast<AShooterCharacter>(GetOwner());

	objectSpawned->AttachToComponent(ownerCharacter->GetMesh1P(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

}

class USkeletalMeshComponent* UObjectInHandManager::GetSkeletalMesh()
{
	//if (Cast<ASurvivalHorrorCharacter>(GetOwner()) != nullptr)
	//{
	//	ASurvivalHorrorCharacter* rick = Cast<ASurvivalHorrorCharacter>(GetOwner());

	//	TArray<UActorComponent*> skeletalMeshes = rick->GetComponentsByClass(USkeletalMeshComponent::StaticClass());

	//	USkeletalMeshComponent* rickSkeleton = nullptr;
	//	for (UActorComponent* mesh : skeletalMeshes)
	//	{
	//		FString name;
	//		if (Cast<USkeletalMeshComponent>(mesh) != nullptr)
	//		{

	//			mesh->AppendName(name);
	//			if (name == skeletName)
	//			{
	//				rickSkeleton = Cast<USkeletalMeshComponent>(mesh);
	//			}
	//		}
	//	}

	//	FString name;
	//	rickSkeleton->AppendName(name);

	//	return rickSkeleton;
	//}
	//else
	//{
	//	return NULL;
	//}

	return NULL;
}

