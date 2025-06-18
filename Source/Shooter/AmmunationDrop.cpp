// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmunationDrop.h"
#include "ShooterCharacter.h"
#include "AmmunationBelt.h"

void AAmmunationDrop::BeginPlay()
{
	Super::BeginPlay();
	ammunationValue = minValue + FMath::Rand() % maxValue;
}


void AAmmunationDrop::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollision(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (Cast<AShooterCharacter>(OtherActor) != nullptr)
	{
		AShooterCharacter* character = Cast<AShooterCharacter>(OtherActor);
		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, FString::Printf(TEXT("%d"), ammunationValue));

		character->GetAmmunationBelt()->SetIndexAmmunation(ammunationType, character->GetAmmunationBelt()->GetIndexAmmunation(ammunationType) + ammunationValue);

		Destroy();
	}
}