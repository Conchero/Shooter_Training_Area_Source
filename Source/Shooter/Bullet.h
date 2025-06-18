// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();
	UFUNCTION()
		virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void SetSpawner(class AFirearm* _firearm);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* projectileComponent;
	UPROPERTY(EditAnywhere)
		float gravityScale = 0;
	UPROPERTY(EditAnywhere)
		float speed = 5000.f;
	float damage;
	float range;
	FVector finalPos;
	UPROPERTY(BlueprintReadOnly)
	class AFirearm* spawner;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
