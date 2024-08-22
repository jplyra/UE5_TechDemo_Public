// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBGWidgetControllerParams.h"
#include "UObject/Object.h"
#include "BGWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;


UCLASS()
class BGWIDGETSYSTEM_API UBGWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	FBGWidgetControllerParams WidgetParams{};
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FBGWidgetControllerParams& WCParams);

	virtual void BroadcastInitialValues();
	
	virtual void BindCallbacksToDependencies();
};
