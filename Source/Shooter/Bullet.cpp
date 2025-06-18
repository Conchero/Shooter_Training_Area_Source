// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <GameFramework/ProjectileMovementComponent.h>
//#include "../Character/EnemyCharacter.h"
#include "Firearm.h"
//#include "../Character/ShadowCharacter.h"
//#include "../Stats/HealthComponent.h"
#include <Components/CapsuleComponent.h>
#include "EnemyCharacter.h"
#include "CharacterStats.h"
#include "HealthComponent.h"
#include "ElementalComponent.h"
#include "EWeaponElementType.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	mesh->SetupAttachment(RootComponent);
	projectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");

	projectileComponent->bInitialVelocityInLocalSpace = true;
	projectileComponent->InitialSpeed = speed;
	projectileComponent->MaxSpeed = speed;
	projectileComponent->ProjectileGravityScale = gravityScale;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABullet::OnCollision);
	//InitialLifeSpan = 100;
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AEnemyCharacter>(OtherActor) != nullptr)
	{
		AEnemyCharacter* enemy = Cast<AEnemyCharacter>(OtherActor);
		enemy->RemoveLife(damage,EWeaponElementType::NONE);
		if (FMath::Rand() % 100 < spawner->GetElementalComponent()->elementalChance)
		{
			enemy->GetAffectedByElement(spawner->GetElementalComponent()->GetWeaponElement(), spawner);
		}
		Destroy();
	}
	
}

void ABullet::SetSpawner(AFirearm* _firearm)
{
	spawner = _firearm;
	damage = _firearm->GetDamageDealt();
	range = _firearm->GetRange();
	InitialLifeSpan = (range*10) / speed;
}
