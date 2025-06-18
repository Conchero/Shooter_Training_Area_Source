// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Collectibles.generated.h"


UCLASS()
class SHOOTER_API ACollectibles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectibles();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UWidgetComponent* collectibleInfo;

	UPROPERTY(BlueprintReadWrite)
		bool ShowCollectibleInfo = false;

	void DestroyCollectible();


	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> objectReference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AActor* objectReferenceInstance;

protected:

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* mesh;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
