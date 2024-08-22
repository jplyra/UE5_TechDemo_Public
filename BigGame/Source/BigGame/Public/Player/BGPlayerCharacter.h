// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BGGasCharacter.h"
#include "InputActionValue.h"
#include "BGPlayerCharacter.generated.h"

class UBGGadgetData;
class UInputAction;
class UInputMappingContext;

class USpringArmComponent;

class UCameraComponent;

UCLASS()
class BIGGAME_API ABGPlayerCharacter final : public ABGGasCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditDefaultsOnly, Category= "Input Config")
	TObjectPtr<UInputAction> MoveInputAction{};

	FDelegateHandle OnGadgetAddedHandle{};
	
	FDelegateHandle OnGadgetRemovedHandle{};
	
public:
	ABGPlayerCharacter();

private:
	void OnAbilityInputPressed(const int32 InputID) const;
	
	void OnAbilityInputReleased(const int32 InputID) const;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual EBGDamageTeam GetDamageTeam() override;

private:
	void BindInputs();

	void HandleMoveActionTriggered(const FInputActionValue& InputValue);

	void HandleMoveActionCompleted(const FInputActionValue& InputValue);

	void HandleInventoryEventBinding(bool bBind);

	UFUNCTION()
	void OnGadgetAdded(UBGGadgetData* Gadget);

	UFUNCTION()
	void OnGadgetRemoved(UBGGadgetData* Gadget);
};
