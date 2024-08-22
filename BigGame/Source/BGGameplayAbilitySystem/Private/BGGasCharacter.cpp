// Fill out your copyright notice in the Description page of Project Settings.


#include "BGGasCharacter.h"
#include "BGCharacterDefaultAttributes.h"
#include "BGGasCharacterDefaults.h"
#include "BGGasAbility.h"
#include "BGGasAttributeSet.h"
#include "BGGasComponent.h"
#include "BGGasSettings.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBGGasCharacter, Log, All)

ABGGasCharacter::ABGGasCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* ABGGasCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABGGasCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitializeDefaultCharacterDataAsset();
}

void ABGGasCharacter::InitializeDefaultAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	if (!DefaultAbilities)
	{
		UE_LOG(LogBGGasCharacter, Error, TEXT("Gas character does not contains a valid DefaultAbilities data asset."));
		return;
	}

	for (FBGGameplayInputAbilityInfo& StartupAbility : DefaultAbilities->InputAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(StartupAbility.GameplayAbilityClass, 1, StartupAbility.AutoGeneratedInputID);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	for (TSubclassOf<UBGGasAbility> Ability: DefaultAbilities->NonInputAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1,-1, this));
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;

	SetIsGrounded(true);
}

void ABGGasCharacter::InitializeDefaultAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!DefaultAbilities)
	{
		UE_LOG(LogBGGasCharacter, Error, TEXT("Gas character does not contains a valid DefaultAbilities data asset."));
		return;
	}

	if (!DefaultAbilities->DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAbilities->DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}

	BindGasDelegates();
}

void ABGGasCharacter::InitializeStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->bStartupEffectsApplied)
	{
		return;
	}

	if (!DefaultAbilities)
	{
		UE_LOG(LogBGGasCharacter, Error, TEXT("Gas character does not contains a valid DefaultAbilities data asset."));
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (const TSubclassOf<UBGGasEffect> GameplayEffect : DefaultAbilities->StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->bStartupEffectsApplied = true;
}

void ABGGasCharacter::InitializeDefaultCharacterDataAsset()
{
	if (!DefaultCharacterAttributes)
	{
		UE_LOG(LogBGGasCharacter, Error, TEXT("Default attributes data asset is invalid."))
		return;
	}

	UCharacterMovementComponent* MoveComponent = GetCharacterMovement();
	MoveComponent->GravityScale = DefaultCharacterAttributes->GravityScale;
	MoveComponent->MaxWalkSpeed = DefaultCharacterAttributes->MoveSpeed;
	MoveComponent->MaxAcceleration = DefaultCharacterAttributes->MoveAcceleration;
	MoveComponent->JumpZVelocity = DefaultCharacterAttributes->JumpVelocity;
	MoveComponent->AirControl = DefaultCharacterAttributes->AirControl;
	MoveComponent->AirControlBoostMultiplier = DefaultCharacterAttributes->AirControlMultiplier;
	MoveComponent->BrakingFriction = DefaultCharacterAttributes->BreakingAcceleration;
	MoveComponent->BrakingFrictionFactor = DefaultCharacterAttributes->BreakingFrictionMultiplier;
}

void ABGGasCharacter::BindGasDelegates()
{
	if (AttributeSet)
	{
		AttributeSet->OnMoveSpeedChange.BindUObject(this, &ABGGasCharacter::OnMoveSpeedAttributeChanged);
	}
}

void ABGGasCharacter::OnMoveSpeedAttributeChanged(float NewValue) const
{
	UE_LOG(LogBGGasCharacter, Log, TEXT("New move speed: %f"), NewValue)
	
	GetCharacterMovement()->MaxWalkSpeed = NewValue;
}

UBGCharacterDefaultAttributes* ABGGasCharacter::GetDefaultAttributes() const
{
	return DefaultCharacterAttributes;
}

void ABGGasCharacter::AddLooseGameplayTag(FGameplayTag Tag)
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->AddLooseGameplayTag(Tag);
		GetAbilitySystemComponent()->SetTagMapCount(Tag, 1);
	}
}

void ABGGasCharacter::RemoveLooseGameplayTag(FGameplayTag Tag)
{
	if (GetAbilitySystemComponent())
	{
		GetAbilitySystemComponent()->RemoveLooseGameplayTag(Tag);
	}
}

bool ABGGasCharacter::HasGasTag(FGameplayTag Tag) const
{
	return GetAbilitySystemComponent() && GetAbilitySystemComponent()->GetTagCount(Tag) > 0;
}

void ABGGasCharacter::GetHealthValues(float& Current, float& Max)
{
	if (AttributeSet)
	{
		Current = AttributeSet->GetHealth();
		Max = AttributeSet->GetMaxHealth();
	}
}

void ABGGasCharacter::GetSpeedValues(float& MoveSpeed)
{
	if (AttributeSet)
	{
		MoveSpeed = AttributeSet->GetMoveSpeed();
	}
}

void ABGGasCharacter::GetCombatValues(float& Armor, float& BaseAttackPower, float& Poise)
{
	if (AttributeSet)
	{
		Armor = AttributeSet->GetArmor();
		BaseAttackPower = AttributeSet->GetBaseAttack();
		Poise = AttributeSet->GetPoise();
	}
}

void ABGGasCharacter::GetKiValues(float& Current, float& Max)
{
	if (AttributeSet)
	{
		Current = AttributeSet->GetKi();
		Max = AttributeSet->GetMaxKi();
	}
}

void ABGGasCharacter::ApplyDamage(FBGDamage Damage)
{
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const UBGGasSettings* GasSettings = GetDefault<UBGGasSettings>();
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GasSettings->DamageEffectClass, 1.0f, EffectContextHandle);
	
	if (EffectSpecHandle.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(GasSettings->DamageTag, Damage.DamageBase);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
	
	if (AttributeSet)
	{
		if(const float CurrentHealth = AttributeSet->GetHealth(); CurrentHealth <= 0)
		{
			const FGameplayEventData DeadEventData{};
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GasSettings->OnDeadEventTag, DeadEventData);
			return;
		}

		const float PoiseDiff = Damage.DamageHitImpact - AttributeSet->GetPoise();

		if (PoiseDiff <= 0)
		{
			return;
		}
		
		FGameplayEventData OnHitEventData{};
		OnHitEventData.Instigator = Damage.DamageInstigator;
		OnHitEventData.EventMagnitude = PoiseDiff;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GasSettings->OnHitEventTag, OnHitEventData);
	}
}

EBGDamageTeam ABGGasCharacter::GetDamageTeam()
{
	return EBGDamageTeam::None;
}

void ABGGasCharacter::RotateToLookDirection(float DeltaSeconds, float RotationSpeed)
{
	const float CurrentYaw = GetActorRotation().Yaw;
	const float TargetYaw = FRotationMatrix::MakeFromXZ(LookDirection, FVector::UpVector).Rotator().Yaw;

	const float EndYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaSeconds, RotationSpeed);
	const FRotator EndRotator = FRotator(0, EndYaw, 0);
	SetActorRotation(EndRotator);
}

void ABGGasCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	SetIsGrounded(false);
}

void ABGGasCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	SetIsGrounded(true);
}

void ABGGasCharacter::OnWalkingOffLedge_Implementation(const FVector& PreviousFloorImpactNormal, const FVector& PreviousFloorContactNormal, const FVector& PreviousLocation, float TimeDelta)
{
	Super::OnWalkingOffLedge_Implementation(PreviousFloorImpactNormal, PreviousFloorContactNormal, PreviousLocation, TimeDelta);

	SetIsGrounded(false);
}

void ABGGasCharacter::SetIsGrounded(bool bIsGrounded)
{
	if (const UBGGasSettings* Settings = GetDefault<UBGGasSettings>())
	{
		if (bIsGrounded)
		{
			RemoveLooseGameplayTag(Settings->IsFallingTag);
			AddLooseGameplayTag(Settings->IsGroundedTag);
		}
		else
		{
			AddLooseGameplayTag(Settings->IsFallingTag);
			RemoveLooseGameplayTag(Settings->IsGroundedTag);
		}
	}
}

void ABGGasCharacter::HideMesh() const
{
	if (GetMesh())
	{
		GetMesh()->SetVisibility(false);
	}
}

void ABGGasCharacter::ShowMesh() const
{
	if (GetMesh())
	{
		GetMesh()->SetVisibility(true);
	}
}
