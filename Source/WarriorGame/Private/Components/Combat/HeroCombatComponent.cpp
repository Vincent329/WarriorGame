// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/WarriorHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "WarriorDebugHelper.h"

// handy helper function to allow uds to get in the warrior hero weapon
AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
    return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
    return Cast<AWarriorHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedDamageAtLevel(float InLevel) const
{
    return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel); // the Hero weapon has Weapon data (from the Weapon
}

// This handles the logic of sharing the tags to the target in order to affect them
void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
    if (OverlappedActors.Contains(HitActor))
    {
        return; // making sure we can only the actors once per attack
    }

    OverlappedActors.AddUnique(HitActor); // don't forget to clear this array when the attack ends

    // Hold a Data Container for the damage causer and the actor that got hit.
    FGameplayEventData Data;
    Data.Instigator = GetOwningPawn();
    Data.Target = HitActor;

    // Upon contact with the target actor, the gameplay effect waits for the specified tag.  and if it matches, it'll trigger the tag
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),
        WarriorGameplayTags::Shared_Event_MeleeHit,
        Data);

    // Upon contact with the target actor, We're going to just send the hit pause event
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),
        WarriorGameplayTags::Player_Event_HitPause,
        FGameplayEventData());
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{

    
    // once it's pulled from the actor
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(),
        WarriorGameplayTags::Player_Event_HitPause,
        FGameplayEventData());
}
