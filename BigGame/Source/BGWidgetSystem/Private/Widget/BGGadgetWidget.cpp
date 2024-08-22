// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BGGadgetWidget.h"

#include "BGInventorySystem/Public/BGGadgetData.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UBGGadgetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UBGGadgetWidget::CloseWidget);
	}
}

void UBGGadgetWidget::InitializeWidget(UBGGadgetData* GadgetData)
{
	if (GadgetData)
	{
		if (GadgetNameText)
		{
			GadgetNameText->SetText(GadgetData->GadgetName);
		}
		if (GadgetTitleText)
		{
			GadgetTitleText->SetText(GadgetData->GadgetTitle);
		}
		if (GadgetSubTitleText)
		{
			GadgetSubTitleText->SetText(GadgetData->GadgetSubTitle);
		}
		if (GadgetDescriptionText)
		{
			GadgetDescriptionText->SetText(GadgetData->GadgetDescription);
		}
		if (GadgetIconImage)
		{
			GadgetIconImage->SetBrushFromTexture(GadgetData->GadgetIcon);
		}
	}
}

void UBGGadgetWidget::CloseWidget()
{
	RemoveFromParent();
}

void UBGGadgetWidget::SetPlayerController(APlayerController* PlayerController)
{
	OwningPlayerController = PlayerController;
}
