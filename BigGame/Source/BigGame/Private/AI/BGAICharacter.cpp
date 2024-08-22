// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BGAICharacter.h"

#include "BGGasAttributeSet.h"
#include "BGGasComponent.h"


ABGAICharacter::ABGAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UBGGasComponent>(TEXT("GASComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UBGGasAttributeSet>(TEXT("AttributeSet"));
}

void ABGAICharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		InitializeDefaultCharacterDataAsset();
		InitializeDefaultAttributes();
		InitializeStartupEffects();
		InitializeDefaultAbilities();
	}
}