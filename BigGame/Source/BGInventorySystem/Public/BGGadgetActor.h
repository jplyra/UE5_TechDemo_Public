// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGActor.h"
#include "BGGadgetActor.generated.h"

class UBGGadgetData;

UCLASS()
class BGINVENTORYSYSTEM_API ABGGadgetActor : public ABGActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Config")
	TObjectPtr<UBGGadgetData> GadgetData{};
};
