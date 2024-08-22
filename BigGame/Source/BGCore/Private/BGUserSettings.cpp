// Fill out your copyright notice in the Description page of Project Settings.


#include "BGUserSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BGUserSettings)

UBGUserSettings::UBGUserSettings()
{
	CategoryName = "BG";
}

FName UBGUserSettings::GetContainerName() const
{
	return "Project";
}

#if WITH_EDITOR
FText UBGUserSettings::GetSectionText() const
{
	FString Text = Super::GetSectionText().ToString();
	Text.RemoveFromStart("BG");
	Text.RemoveFromEnd("Settings");
	return FText::FromString(Text);
}
#endif