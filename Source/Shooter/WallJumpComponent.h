// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WallJumpComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UWallJumpComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	void SetMovementModeToWallJump();
	void SetMovementModeToNormal();

	int32 GetCustomMovementMode();
};
