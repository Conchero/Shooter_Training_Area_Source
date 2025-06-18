// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory.h"
#include "InHandInventory.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UInHandInventory : public UInventory
{
	GENERATED_BODY()
public:
	UInHandInventory();
	virtual void BeginPlay();
protected:

};
