// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BGPlayerState.h"

ABGPlayerState::ABGPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBGGasComponent>(TEXT("GASComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBGGasAttributeSet>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;
}
