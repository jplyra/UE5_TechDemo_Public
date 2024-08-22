// Fill out your copyright notice in the Description page of Project Settings.


#include "BGInventorySubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(LogBgInventorySubsystem, Log, All)

void UBGInventorySubsystem::AddGadget(UBGGadgetData* GadgetData)
{
	if (!GadgetData)
	{
		UE_LOG(LogBgInventorySubsystem, Log, TEXT("Failed to add new gadget because the data asset is invalid."));
		return;
	}
	
	Gadgets.Add(GadgetData);
	
	OnGadgetAdded.Broadcast(GadgetData);
}

bool UBGInventorySubsystem::RemoveGadget(UBGGadgetData* GadgetData)
{
	if (!GadgetData)
	{
		UE_LOG(LogBgInventorySubsystem, Log, TEXT("Failed to remove gadget because the data asset is invalid."));
		return false;
	}
	
	const bool WasRemoved = Gadgets.Remove(GadgetData) > 0;

	if (WasRemoved)
	{
		OnGadgetRemoved.Broadcast(GadgetData);
	}
	
	return WasRemoved;
}

bool UBGInventorySubsystem::HasGadget(UBGGadgetData* GadgetData) const
{
	return Gadgets.Contains(GadgetData);
}
