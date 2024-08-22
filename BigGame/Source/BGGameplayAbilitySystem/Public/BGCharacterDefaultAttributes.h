// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BGCharacterDefaultAttributes.generated.h"

UCLASS()
class BGGAMEPLAYABILITYSYSTEM_API UBGCharacterDefaultAttributes : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float GravityScale = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float MoveSpeed = 600;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float SprintMoveSpeed = 1000;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float MoveAcceleration = 4080;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float RotationSpeed = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float BreakingFrictionMultiplier = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float BreakingAcceleration = 2048;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Air Movement")
	float JumpVelocity = 800;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Air Movement")
	float DoubleJumpVelocity = 1600;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Air Movement")
	float JumpMaxHoldTime = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Air Movement")
	float AirControl = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Air Movement")
	float AirControlMultiplier = 2;
};
