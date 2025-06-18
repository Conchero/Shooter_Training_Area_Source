// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectibles.h"
#include "ShooterCharacter.h"
#include "InHandInventory.h"
#include <Components/WidgetComponent.h>
#include "Camera/CameraComponent.h"
#include <Kismet/KismetMathLibrary.h>
// Sets default values
ACollectibles::ACollectibles()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectibleMesh"));
	mesh->SetupAttachment(RootComponent);
	collectibleInfo = CreateDefaultSubobject<UWidgetComponent>("collectibleInfo");
	collectibleInfo->SetupAttachment(RootComponent);
}

//void ACollectibles::GetDistRickToCollectible()
//{
//
//	//diffRickCollectible.X = FMath::Abs(GetActorLocation().X - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().X);
//	//diffRickCollectible.Y = FMath::Abs(GetActorLocation().Y - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().Y);
//	//diffRickCollectible.Z = FMath::Abs(GetActorLocation().Z - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation().Z);
//
//	//if (Cast<ASurvivalHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()) != nullptr)
//	//{
//	//	ASurvivalHorrorCharacter* rick = Cast<ASurvivalHorrorCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
//
//	//	if (diffRickCollectible.X <= distCollectible && diffRickCollectible.Y <= distCollectible)
//	//	{
//	//		if (rick->GetInHandInventory()->HasAnEmptySlot() == true)
//	//		{
//	//			//rick->SetObjectToCollect(this);
//	//			isCollectable = true;
//	//		}
//	//	}
//	//	else if (isCollectable == true)
//	//	{
//	//		//rick->SetObjectToCollect(nullptr);
//	//		isCollectable = false;
//	//	}
//	//}
//
//}

//void ACollectibles::IsCollectableChange(bool _b)
//{
//	//if (isCollectable != _b)
//	//{
//	//	isCollectable = _b;
//	//}
//}

// Called when the game starts or when spawned
void ACollectibles::BeginPlay()
{
	Super::BeginPlay();
	
	mesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACollectibles::OnCollision);

	//if (objectReference != nullptr)
	//{
	//	objectReferenceInstance = GetWorld()->SpawnActor<AActor>(objectReference, GetActorLocation(), FRotator::ZeroRotator);

	//	objectReferenceInstance->SetActorHiddenInGame(true);
	//}
	//else
	//{
	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("ygyg")));
	//}
}

void ACollectibles::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ACollectibles::DestroyCollectible()
{
	if (objectReferenceInstance != nullptr)
	{
		objectReferenceInstance->Destroy();
	}
	this->Destroy();


}

// Called every frame
void ACollectibles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetDistRickToCollectible();

	//collectibleInfo->SetVisibility(ShowCollectibleInfo);
	AShooterCharacter* character = Cast<AShooterCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (character != nullptr)
	{
		FVector lookAtPlayer = (character->GetFirstPersonCameraComponent()->GetForwardVector() * -1);


		collectibleInfo->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(lookAtPlayer));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), isCollectable));

}

