// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectInHandManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UObjectInHandManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectInHandManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
	class AActor* objectSpawned;
	UPROPERTY(EditAnywhere)
	FString skeletName = "CharacterMesh1P";

	//ToRemove if used on other project 
	void CheckFirearm(class AActor* _objectToCheck);
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		 TSubclassOf<class AActor> object;

	class AActor* GetObjectSpawned() { return objectSpawned; };

	UFUNCTION(BlueprintCallable)
		void SpawnObjectInHand(TSubclassOf<class AActor> _objectToSpawn);

	UFUNCTION(BlueprintCallable)
		void GetBareHand();

	void AttachToPawn();



	class USkeletalMeshComponent* GetSkeletalMesh();
};
