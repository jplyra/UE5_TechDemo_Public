// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BGUserSettings.generated.h"

UCLASS(Config="BG", DefaultConfig, Abstract)
class BGCORE_API UBGUserSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBGUserSettings();

	virtual FName GetContainerName() const override;

#if WITH_EDITOR
	virtual FText GetSectionText() const override;
#endif
};
