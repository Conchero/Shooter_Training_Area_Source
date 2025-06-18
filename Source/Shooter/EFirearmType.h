// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum EFirearmType
{
	RIFLE UMETA(DisplayName = "Rifle"),
	PISTOL UMETA(DisplayName = "Pistol"),
	SHOTGUN UMETA(DisplayName = "Shotgun"),
	SNIPER UMETA(DisplayName = "Sniper"),
	TYPE_COUNT UMETA(DisplayName = "TYPE_COUNT"),
};
