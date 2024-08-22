// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BGHUD.h"

#include "BGInventorySubsystem.h"
#include "Widget/BGUserWidget.h"
#include "Widget/BGGadgetWidget.h"
#include "WidgetController/BGOverlayWidgetController.h"

DEFINE_LOG_CATEGORY_STATIC(LogBGHUD, Log, All)

UBGOverlayWidgetController* ABGHUD::GetOverlayWidgetController(const FBGWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UBGOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ABGHUD::InitOverlay(const FBGWidgetControllerParams& WCParams)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unintialized, please fill out BP_AuraHUD"))
	checkf(OverlayWidgetControllerClass,
	       TEXT("Overlay Widget Controller Class unintialized, please fill out BP_AuraHUD"))

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UBGUserWidget>(Widget);

	UBGOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);

	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}

void ABGHUD::ShowGadgetWidget(UBGGadgetData* GadgetData)
{
	if (!GadgetWidgetClass)
	{
		UE_LOG(LogBGHUD, Log, TEXT("Failed to show gadget widget because the GadgetWidgetClass is invalid."));
		return;
	}

	UBGGadgetWidget* GadgetWidget = CreateWidget<UBGGadgetWidget>(GetWorld(), GadgetWidgetClass);
	GadgetWidget->SetPlayerController(GetOwningPlayerController());
	GadgetWidget->InitializeWidget(GadgetData);
	GadgetWidget->AddToViewport();
}

void ABGHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UBGInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UBGInventorySubsystem>())
	{
		OnAddedGadgetHandle = InventorySubsystem->OnGadgetAdded.AddUObject(this, &ABGHUD::ShowGadgetWidget);
	}
}

void ABGHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UBGInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UBGInventorySubsystem>(); OnAddedGadgetHandle.IsValid())
	{
		InventorySubsystem->OnGadgetAdded.Remove(OnAddedGadgetHandle);
	}

	Super::EndPlay(EndPlayReason);
}
