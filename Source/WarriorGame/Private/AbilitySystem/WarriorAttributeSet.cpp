// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

// Called whenever an attribute has been modified, Look for GEExec_Calc as the effect is executed from there
void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor()); // FGameplayEffectModCallbackData gives us the GameplayEffect spec (damage), the Evaluated Data (the attribute to find like Health/Rage/Damage), and the Target (the actor in question)
						// works the same as casting to the Interface
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();  // we can get the UI component because the UPawnUIComponent is forward declared in the Interface

	checkf(PawnUIComponent, TEXT("Couldn't extract a Pawn UI Component from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());


	// nothing goes on in parent
	// access the header file from FGameplayEffectModCallbackData in order to access data, NOTE: no cpp file so you'd have to include the header directly
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());
		
		SetCurrentHealth(NewCurrentHealth); // because of Attribute Accessors, we can directly access the attribute as such

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth()/GetMaxHealth());
	}

	// for now the these don't do anything, Develop Rage Multiplier later
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		const float NewCurrentRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());
		SetCurrentRage(NewCurrentRage);

		// Since Rage is Hero specific, our Pawn has to be casted or communicated as a Hero UI Component... interface it
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{ 
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage()/GetMaxRage());
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();
		
		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(TEXT("Old Health: %f, Damage Done: %f, New Current Health: %f"),
		OldHealth,
		DamageDone,
		NewCurrentHealth
		);

		// DEBUG STRING: WILL REMOVE LATER
		// Debug::Print(DebugString, FColor::Green);	
		// TO-DO: Notify the UI

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());


		// we will now know what the value of the new current health is and check to see if the target actor is dead or not
		if (NewCurrentHealth == 0.f)
		{
			// From the Data Struct, we have access to the data type of Target (meaning the object/AbilitySystemComponent that we're intending to deal damage to)
			UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Dead);
		}
	}

}
