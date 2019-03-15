// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EMovesetEnum : uint8
{
    M_Default	UMETA(DisplayName="Default"),
	M_Helicopter UMETA(DisplayName="Helicopter"),
	M_Balloon UMETA(DisplayName="Ballon")
};
