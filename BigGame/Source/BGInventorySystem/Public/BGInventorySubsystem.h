// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGGadgetData.h"
#include "BGCore/Public/BGGameInstanceSubsystem.h"
#include "BGInventorySubsystem.generated.h"

UCLASS()
class BGINVENTORYSYSTEM_API UBGInventorySubsystem : public UBGGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	TSet<TObjectPtr<UBGGadgetData>> Gadgets{};
	
public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FBGOnGadgetInventoryChanged, UBGGadgetData*)

	FBGOnGadgetInventoryChanged OnGadgetAdded{};

	FBGOnGadgetInventoryChanged OnGadgetRemoved{};
	
	UFUNCTION(BlueprintCallable)
	void AddGadget(UBGGadgetData* GadgetData);

	UFUNCTION(BlueprintCallable)
	bool RemoveGadget(UBGGadgetData* GadgetData);

	UFUNCTION(BlueprintPure)
	bool HasGadget(UBGGadgetData* GadgetData) const;
};
