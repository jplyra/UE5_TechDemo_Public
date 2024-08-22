// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "BGUserWidget.generated.h"

class UBGWidgetController;

UCLASS()
class BGWIDGETSYSTEM_API UBGUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBGWidgetController> WidgetController{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bShowMouseWhenInitialized = false;
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UBGWidgetController* InWidgetController);

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet(UBGWidgetController* NewWidgetController);

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
};
