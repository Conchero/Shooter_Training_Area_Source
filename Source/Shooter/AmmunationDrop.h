// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EFirearmType.h"
#include "Collectibles.h"
#include "AmmunationDrop.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AAmmunationDrop : public ACollectibles
{
	GENERATED_BODY()
public:
		virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TEnumAsByte<EFirearmType> ammunationType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 ammunationValue;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere)
	int32 minValue;

	UPROPERTY(EditAnywhere)
		int32 maxValue;
};
