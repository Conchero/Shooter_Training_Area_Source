// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<class TSubclassOf<class AActor>> objects;

	int32 slotSelected = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetObjectIninventory(TSubclassOf<class AActor> _object, int _index);
	UFUNCTION(BlueprintCallable)
	class TSubclassOf<class AActor> GetObjectIninventory(int _index) { return objects[_index]; };
	UFUNCTION(BlueprintCallable)
	TArray<class TSubclassOf<class AActor>> GetSlots() { return objects; };
	UFUNCTION(BlueprintCallable)
	void SetSlotSelected(float _v) { slotSelected = _v; };
	UFUNCTION(BlueprintCallable)
	int GetSlotSelected() { return slotSelected; };
	UFUNCTION(BlueprintCallable)
	bool HasAnEmptySlot();
	UFUNCTION(BlueprintCallable)
	int GetUIImageIndex(int _index);
	UFUNCTION(BlueprintCallable)
		int GetFreeSlot();
	UFUNCTION(BlueprintCallable)
		class AShooterCharacter* GetOwnerCharacter();
};
