// Fill out your copyright notice in the Description page of Project Settings.


#include "BGCombatFunctionLibrary.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogBgCombatSystemLibrary, Log, All)

bool UBGCombatFunctionLibrary::TryApplyDamage(AActor* Instigator, AActor* CombatTarget, FBGDamage Damage)
{
	if (!IsValid(Instigator) || !IsValid(CombatTarget))
	{
		UE_LOG(LogBgCombatSystemLibrary, Warning, TEXT("Instigator or CombatTarget is null."));
		return false;
	}
	
	if (IBGDamageable* InstigatorInterface = Cast<IBGDamageable>(Instigator); IBGDamageable* CombatTargetInterface = Cast<IBGDamageable>(CombatTarget))
	{
		if ((InstigatorInterface->GetDamageTeam() != CombatTargetInterface->GetDamageTeam()) && CombatTargetInterface->GetDamageTeam() != EBGDamageTeam::None)
		{
			UE_LOG(LogBgCombatSystemLibrary, Log, TEXT("Damage was applied."));
			CombatTargetInterface->ApplyDamage(Damage);
			return true;
		}

		UE_LOG(LogBgCombatSystemLibrary, Log, TEXT("Invalid team, does not take damage."));
		return false;
	}

	UE_LOGFMT(LogBgCombatSystemLibrary, Log, "Some of actors does not implements BGDamageable interface. Instigator {0} and CombatTarget {1}", Instigator->GetName(), CombatTarget->GetName());
	return false;
}
