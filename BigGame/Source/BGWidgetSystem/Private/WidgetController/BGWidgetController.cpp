// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/BGWidgetController.h"

void UBGWidgetController::SetWidgetControllerParams(const FBGWidgetControllerParams& WCParams)
{
	WidgetParams = WCParams;
}

void UBGWidgetController::BroadcastInitialValues()
{
}

void UBGWidgetController::BindCallbacksToDependencies()
{
}
