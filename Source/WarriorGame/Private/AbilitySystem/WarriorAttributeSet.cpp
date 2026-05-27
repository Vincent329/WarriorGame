// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// nothing goes on in parent
	// access the header file from FGameplayEffectModCallbackData in order to access data, NOTE: no cpp file so you'd have to include the header directly
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		
		SetCurrentHealth(NewCurrentHealth);
	}

	// for now the these don't do anything, Develop Rage Multiplier later
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		// TO-DO: Notify the UI
		const FString DebugString = FString::Printf(TEXT("Old Health: %f, Damage Done: %f, New Current Health: %f"),
		OldHealth,
		DamageDone,
		NewCurrentHealth
		);

		// DEBUG STRING: WILL REMOVE LATER
		// Debug::Print(DebugString, FColor::Green);


		// we will now know what the value of the new current health is and check to see if the target actor is dead or not
		if (NewCurrentHealth == 0.f)
		{
			// From the Data Struct, we have access to the data type of Target (meaning the object/AbilitySystemComponent that we're intending to deal damage to)
			UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead);
		}
	}

}
