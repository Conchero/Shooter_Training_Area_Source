// Fill out your copyright notice in the Description page of Project Settings.


#include "WallJumpComponent.h"
#include "EnumCustomMovement.h"

void UWallJumpComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	switch ((EMovementModeCustom)CustomMovementMode)
	{
	case EMovementModeCustom::CUSTOM_NONE:
		break;

	case EMovementModeCustom::CUSTOM_WALL_JUMP:
		break;

	default:
		break;
	}

}

void UWallJumpComponent::SetMovementModeToWallJump()
{
	if (CustomMovementMode == EMovementModeCustom::CUSTOM_NONE)
	{
		SetMovementMode(MOVE_Falling, EMovementModeCustom::CUSTOM_WALL_JUMP);
		CustomMovementMode = EMovementModeCustom::CUSTOM_WALL_JUMP;
	}
}

void UWallJumpComponent::SetMovementModeToNormal()
{
	if (CustomMovementMode == EMovementModeCustom::CUSTOM_WALL_JUMP)
	{
		SetMovementMode(MOVE_Falling, EMovementModeCustom::CUSTOM_NONE);
		CustomMovementMode = EMovementModeCustom::CUSTOM_NONE;
	}
}

int32 UWallJumpComponent::GetCustomMovementMode()
{
	return (EMovementModeCustom)CustomMovementMode;
}
