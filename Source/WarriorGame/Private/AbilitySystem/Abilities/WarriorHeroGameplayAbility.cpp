// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "WarriorGameplayTags.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
    if (!CachedWarriorHeroCharacter.IsValid())
    { 
        CachedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);  // function was originally const, but since we have to store reference data into the cached warrior, it cannot be const
    }

    return CachedWarriorHeroCharacter.IsValid() ? CachedWarriorHeroCharacter.Get() : nullptr; // depending on the result of isValid, we return either WarriorCharacter using the Get function, or a nullptr
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
    if (!CachedWarriorHeroController.IsValid())
    {
        CachedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController);
    }
    
    return CachedWarriorHeroController.IsValid() ? CachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
    return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

// What we're creating here is 
FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
    check(EffectClass);
    
    //RESEARCH THIS, how the heck would I know about this off the bat
    FGameplayEffectContextHandle ContextHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo()); // the effect instigator and causer, in this case, will be the same actor

    // IN THE EDITOR, We're using the GE_Shared_DealDamage Gameplay Effect to base our calculations
    FGameplayEffectSpecHandle EffectSpecHandle 
    = GetWarriorAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
        EffectClass,
        GetAbilityLevel(), // from the gameplay ability class, I would not know this from the start
        ContextHandle // created from above
    );
    
    // stored the weapon base damage to the spec handle
    EffectSpecHandle.Data->SetSetByCallerMagnitude(
        WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
        InWeaponBaseDamage
    ); // Data is a type of TSharedPointer of GameplayEffectSpec.  Can be used like a regular pointer to the handle


    // this is how we're oging to check the 
    if (InCurrentAttackTypeTag.IsValid())
    {
        // store the combo count in the spec handle
        // So checking whether or not it's light or Heavy, and the combo count within that
        // then we can calculate the damage from there
        EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
    }

    return EffectSpecHandle;

}
