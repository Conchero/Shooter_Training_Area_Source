// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EHealthType
{
	BLOOD UMETA(DisplayName = "BLOOD"),
	SHIELD UMETA(DisplayName = "SHIELD"),
	ARMOR UMETA(DisplayName = "ARMOR"),
	MAX_HEALTH UMETA(DisplayName = "MAX_HEALTH"),
};