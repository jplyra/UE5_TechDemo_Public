// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "BGGadgetData.generated.h"

class UTexture2D;

class UBGGasAbility;

UCLASS()
class BGINVENTORYSYSTEM_API UBGGadgetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tag")
	FGameplayTag GadgetTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UBGGasAbility> GadgetAbilityClass{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Description")
	FText GadgetName{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Description")
	FText GadgetTitle{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Description")
	FText GadgetSubTitle{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Description")
	FText GadgetDescription{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Description")
	TObjectPtr<UTexture2D> GadgetIcon{};
};
