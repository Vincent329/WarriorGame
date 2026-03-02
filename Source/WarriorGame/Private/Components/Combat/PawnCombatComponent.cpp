// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Components/BoxComponent.h"

#include "Items/Weapons/WarriorBaseWeapon.h"
#include "WarriorDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A tag named %s has already been added as a carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister); // check if the weapon is valid

	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister); // emplace will put in a default value to the map

	if (bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

}

AWarriorBaseWeapon* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWarriorBaseWeapon* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet)) // const pointers are new to me, are they mainly for maps?
		{
			return *FoundWeapon;
		}

	}

	return nullptr;
}

AWarriorBaseWeapon* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

// executed upon firing the Delegate from the Weapon
void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{

	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
	{
		AWarriorBaseWeapon* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

		check(WeaponToToggle);

		if (bShouldEnable)
		{ 
			WeaponToToggle->GetWeaponCollider()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else {
			WeaponToToggle->GetWeaponCollider()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		}
	}

	// TODO: Handle other collision boxes for the body
	
}

