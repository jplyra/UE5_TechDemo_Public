// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BGDamageable.generated.h"

USTRUCT(BlueprintType)
struct FBGDamage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Damage")
	float DamageBase{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Damage")
	float CriticalChance{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Damage")
	float CriticalBonus{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Damage")
	TObjectPtr<AActor> DamageInstigator{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Damage")
	float DamageHitImpact{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Damage")
	FVector DamageWorldImpulse{ForceInitToZero};
};

UENUM(BlueprintType)
enum class EBGDamageTeam : uint8
{
	None,
	Player,
	Enemy,
	Destructible
};

UINTERFACE()
class UBGDamageable : public UInterface
{
	GENERATED_BODY()
};

class BGCOMBATSYSTEM_API IBGDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintType)
	virtual void ApplyDamage(FBGDamage Damage) = 0;

	UFUNCTION(BlueprintType)
	virtual EBGDamageTeam GetDamageTeam() = 0;

};
