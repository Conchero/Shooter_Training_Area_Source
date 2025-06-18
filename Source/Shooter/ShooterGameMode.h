// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

UCLASS(minimalapi)
class AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterGameMode();

	
	UPROPERTY(EditAnywhere)
	float minutesValue = 1;
	UPROPERTY( BlueprintReadOnly)
		float minutesTimer = minutesValue;
	UPROPERTY(EditAnywhere)
		float secondValue = 60;
	UPROPERTY(BlueprintReadOnly)
		float secondTimer = secondValue;

	virtual  void BeginPlay() override;
};



