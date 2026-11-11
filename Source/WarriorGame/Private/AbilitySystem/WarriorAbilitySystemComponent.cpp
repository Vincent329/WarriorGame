// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h" // replaced WarriorGameplayAbility to fix AbilitySpec bug

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	// this is from the parent Ability System Component: Returns an array of gameplay abilities  
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
	
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue; // once we get past this check, we know that an ability with this tag exists
		
		TryActivateAbility(AbilitySpec.Handle); // Activate the ability in our for loop
	}
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

// HERO SPECIFIC
void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle)
{
	if (InDefaultWeaponAbilities.IsEmpty()) return;

	for (const FWarriorHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant); // make sure to include WarriorHeroGameplayAbility.h

		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		OutGrantedAbilitySpecHandle.AddUnique(GiveAbility(AbilitySpec)); // When we call Give Ability, we're going to store the return value of that function call and place it in the OutGrantedAbilitySpecHandle modifier

	}
	
}

void UWarriorAbilitySystemComponent::RemoveGrantedWeaponAbilities(UPARAM(ref)TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;
	
	for (const FGameplayAbilitySpecHandle& GameplayAbilitySpecHandle : InSpecHandlesToRemove)
	{
		if (GameplayAbilitySpecHandle.IsValid())
		{
			ClearAbility(GameplayAbilitySpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty(); //Any latent abilities, flush out anything
}

bool UWarriorAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
	check(AbilityTagToActivate.IsValid());

	TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
	
	// SingleTagContainer can turn a tag into a tag container
	// We created an array above of ability specs, this will be filled with Activatable Gameplay Abilities
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);
	
	if (!FoundAbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];

		check (SpecToActivate);

		if (!SpecToActivate->IsActive())
		{
			return TryActivateAbility(SpecToActivate->Handle);
		}
	}

	return false;
}