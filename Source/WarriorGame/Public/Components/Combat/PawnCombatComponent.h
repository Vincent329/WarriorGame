// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponentExtensionBase.h"
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

class AWarriorBaseWeapon;

UENUM(BlueprintType) // blueprint type because we want to be able to change this in either the details panel of the anim notify, we can specify a scenario of what's happening
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand, // for enemies, they might have a left or right hand instead of a weapon
	RightHand
};

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UPawnCombatComponent : public UPawnComponentExtensionBase
{
	GENERATED_BODY()

private:
	TMap<FGameplayTag, AWarriorBaseWeapon*> CharacterCarriedWeaponMap; // allows us to store multiple weapons
																	// this course only focuses on 1 weapon, but we can add more if we want

public:
	UFUNCTION(BlueprintCallable, Category = "WarriorCombat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon = false); // Access the TMap to get a weapon
																																					// false when the hero is registering weapons. tru.e for enemies as they'll equip weapons after spawning
	UFUNCTION(BlueprintCallable, Category = "WarriorCombat")
	AWarriorBaseWeapon* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;	// Searches the TMap for the weapon by the tag

	UPROPERTY(BlueprintReadWrite, Category = "WarriorCombat")
	FGameplayTag CurrentEquippedWeaponTag;	// used to keep track of the currently equipped weapon
											// The wepaon itself has to be set in blueprint, hence why the UPROPERTY is set to BlueprintReadWrite
											// Manually set the tag for equipping and manually clear when unequipping
											// also needed for the anim graph

	UFUNCTION(BlueprintCallable, Category = "WarriorCombat")
	AWarriorBaseWeapon* GetCharacterCurrentEquippedWeapon() const;

	virtual void OnHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

	UFUNCTION(BlueprintCallable, Category = "WarriorCombat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

protected:
	TArray<AActor*> OverlappedActors;
};																																					

