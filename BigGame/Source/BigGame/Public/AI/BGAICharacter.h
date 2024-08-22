// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGGasCharacter.h"
#include "BGAICharacter.generated.h"

UCLASS()
class BIGGAME_API ABGAICharacter : public ABGGasCharacter
{
	GENERATED_BODY()

public:
	ABGAICharacter();

protected:
	virtual void BeginPlay() override;
};
