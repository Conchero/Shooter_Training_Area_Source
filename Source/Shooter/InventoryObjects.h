// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryObjects.generated.h"

UCLASS()
class SHOOTER_API AInventoryObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryObjects();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* objectMesh;
	UPROPERTY(EditAnywhere)
	FVector socketOffset = FVector(0.f,0.f,0.f);
	UPROPERTY(EditAnywhere)
		FRotator socketRotation = FRotator(0.f, -0.f, 0.f);
	class AShooterCharacter* owner;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ImageUIIndex;
	FVector GetOffset() { return socketOffset; };
	FRotator GetRotation() { return socketRotation; };

	class AShooterCharacter* GetCharacterOwner() { return owner; };
	void SetCharacterOwner(class AShooterCharacter* _character) { owner = _character; };
};
