// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpableWallComponent.h"
#include <Components/StaticMeshComponent.h>
#include "ShooterCharacter.h"
#include "WallJumpComponent.h"
#include <GameFramework/CharacterMovementComponent.h>

// Sets default values for this component's properties
UJumpableWallComponent::UJumpableWallComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJumpableWallComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()->FindComponentByClass<UStaticMeshComponent>() != nullptr)
		parentMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	// ...
	parentMesh->OnComponentHit.AddUniqueDynamic(this, &UJumpableWallComponent::OnCollision);
	
}


void UJumpableWallComponent::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, GetOwner()->GetActorForwardVector().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, Hit.ImpactNormal.ToString());*/
	if (Cast<AShooterCharacter>(OtherActor) != nullptr)
	{
		AShooterCharacter* character = Cast<AShooterCharacter>(OtherActor);
	
		//ZPropulsion = character->jumpStrenght;
		//FVector launchDir = FVector(-Hit.ImpactNormal.X* propulsionStrenght, -Hit.ImpactNormal.Y* propulsionStrenght, ZPropulsion);
		//if (Hit.ImpactNormal != GetOwner()->GetActorForwardVector() || Hit.ImpactNormal != GetOwner()->GetActorForwardVector() * -1)
		//{

		//	character->LaunchCharacter(launchDir, true, true);
		//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, character->GetVelocity().ToString());
		//}

		//if (Hit.ImpactNormal != GetOwner()->GetActorRightVector() || Hit.ImpactNormal != GetOwner()->GetActorRightVector() * -1)
		//{
		//	character->LaunchCharacter(launchDir, true, true);
		//	//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, character->GetVelocity().ToString());
		//}
	}
}

// Called every frame
void UJumpableWallComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

