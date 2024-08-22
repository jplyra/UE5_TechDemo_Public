// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BGControllableWidget.h"
#include "FBGWidgetControllerParams.h"
#include "BGHUD.generated.h"

class UBGOverlayWidgetController;
class UBGGadgetWidget;
class UBGGadgetData;
class UBGUserWidget;

UCLASS()
class BGWIDGETSYSTEM_API ABGHUD : public AHUD, public IBGControllableWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBGUserWidget> OverlayWidgetClass{};

	UPROPERTY()
	TObjectPtr<UBGOverlayWidgetController> OverlayWidgetController{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBGOverlayWidgetController> OverlayWidgetControllerClass{};

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBGGadgetWidget> GadgetWidgetClass{};

	FDelegateHandle OnAddedGadgetHandle{};

public:
	UPROPERTY()
	TObjectPtr<UBGUserWidget> OverlayWidget{};

	UBGOverlayWidgetController* GetOverlayWidgetController(const FBGWidgetControllerParams& WCParams);

	virtual void InitOverlay(const FBGWidgetControllerParams& WCParams) override;

	void ShowGadgetWidget(UBGGadgetData* GadgetData);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
