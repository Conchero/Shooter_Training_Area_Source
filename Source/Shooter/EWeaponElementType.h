// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum EWeaponElementType
{
	NONE UMETA(DisplayName = "NONE"),
	FIRE UMETA(DisplayName = "FIRE"),
	ELECTRIC UMETA(DisplayName = "ELECTRIC"),
	CORROSIVE UMETA(DisplayName = "CORROSIVE"),
	MAX_ELEMENT UMETA(DisplayName = "MAX_ELEMENT"),
};
