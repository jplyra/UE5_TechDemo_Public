// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBGWidgetControllerParams.h"
#include "UObject/Interface.h"
#include "BGControllableWidget.generated.h"

UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class BGCORE_API UBGControllableWidget : public UInterface
{
	GENERATED_BODY()
};

class BGCORE_API IBGControllableWidget
{
	GENERATED_BODY()

public:
	virtual void InitOverlay(const FBGWidgetControllerParams& WCParams) = 0;
};
