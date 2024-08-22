// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGUserWidget.h"
#include "BGGadgetWidget.generated.h"

class UBGGadgetData;
class UTextBlock;
class UButton;
class UImage;

UCLASS()
class BGWIDGETSYSTEM_API UBGGadgetWidget : public UBGUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GadgetNameText{};

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GadgetTitleText{};

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GadgetSubTitleText{};

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GadgetDescriptionText{};

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> GadgetIconImage{};

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton{};

	UPROPERTY()
	APlayerController* OwningPlayerController{};
	
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeWidget(UBGGadgetData* GadgetData);

	UFUNCTION()
	void CloseWidget();

	void SetPlayerController(APlayerController* PlayerController);
};
