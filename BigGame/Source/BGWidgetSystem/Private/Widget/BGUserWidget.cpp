// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BGUserWidget.h"

#include "Kismet/GameplayStatics.h"

void UBGUserWidget::SetWidgetController(UBGWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet(WidgetController);
}

void UBGUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!IsDesignTime() && GetOwningPlayer() && bShowMouseWhenInitialized)
	{
		GetOwningPlayer()->bShowMouseCursor = true;
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void UBGUserWidget::NativeDestruct()
{
	if (!IsDesignTime() && GetOwningPlayer() && bShowMouseWhenInitialized)
	{
		GetOwningPlayer()->bShowMouseCursor = false;
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	Super::NativeDestruct();
}