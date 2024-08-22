// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BGDamageable.h"
#include "GameplayTags.h"
#include "BGGasCharacter.generated.h"

class UBGCharacterDefaultAttributes;

class UBGGasComponent;

class UBGGasAttributeSet;

class UBGGasCharacterDefaults;

class UAbilitySystemComponent;

class UGameplayEffect;

class UGameplayAbility;

UCLASS()
class BGGAMEPLAYABILITYSYSTEM_API ABGGasCharacter : public ACharacter, public IAbilitySystemInterface, public IBGDamageable
{
	GENERATED_BODY()

public:
	ABGGasCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBGGasComponent> AbilitySystemComponent{};
	
	UPROPERTY()
	TObjectPtr<UBGGasAttributeSet> AttributeSet{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TObjectPtr<UBGGasCharacterDefaults> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TObjectPtr<UBGCharacterDefaultAttributes> DefaultCharacterAttributes{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector MoveDirection{};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector LookDirection{};

protected:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void BeginPlay() override;
	
	virtual void InitializeDefaultAbilities();

	virtual void InitializeDefaultAttributes();

	virtual void InitializeStartupEffects();

	virtual void InitializeDefaultCharacterDataAsset();
	
	void BindGasDelegates();

	UFUNCTION()
	void OnMoveSpeedAttributeChanged(float NewValue) const;

public:
	UFUNCTION(BlueprintPure)
	UBGCharacterDefaultAttributes* GetDefaultAttributes() const;
	
	UFUNCTION(BlueprintCallable)
	void AddLooseGameplayTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	void RemoveLooseGameplayTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	bool HasGasTag(FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable)
	void GetHealthValues(float& Current, float& Max);

	UFUNCTION(BlueprintCallable)
	void GetSpeedValues(float& MoveSpeed);

	UFUNCTION(BlueprintCallable)
	void GetCombatValues(float& Armor, float& BaseAttackPower, float& Poise);

	UFUNCTION(BlueprintCallable)
	void GetKiValues(float& Current, float& Max);

public:
	UFUNCTION(BlueprintCallable)
	virtual void ApplyDamage(FBGDamage Damage) override;

	virtual EBGDamageTeam GetDamageTeam() override;

	UFUNCTION(BlueprintCallable)
	void RotateToLookDirection(float DeltaSeconds, float RotationSpeed);

private:
	virtual void OnJumped_Implementation() override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta) override;

	void SetIsGrounded(bool bIsGrounded);

public:
	UFUNCTION(BlueprintCallable)
	void HideMesh() const;

	UFUNCTION(BlueprintCallable)
	void ShowMesh() const;
};
