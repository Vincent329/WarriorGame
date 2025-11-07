// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"
#include "WarriorStructTypes.generated.h" // remember when creating custom files, to add a generated.h file

class UWarriorHeroLinkedAnimLayer;
class UWarriorHeroGameplayAbility;
class UInputMappingContext;

// add: We moved the struct from the Hero Startup Data and brought it to Struct Types, so that we can use this more freely
USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag")) // MetaData, will filter out all other tags taht aren't set as "InputTag"
	FGameplayTag InputTag; // if you find a squiggly line, you can press F12 to go to the declaration of the data type if it exists and find the include directories needed

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorHeroGameplayAbility> AbilityToGrant;

	bool IsValid() const; // we want to check if the Ability to grant
};

USTRUCT(BlueprintType)
struct FWarriorHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf< UWarriorHeroLinkedAnimLayer> WeaponAnimLayerToLink; // can be extended to account for multiple weapons, different Animation Layers for weapons of our choice

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext; // the weapon mapping context currently active (When a weapon is equipped, swap mapping contexts to account for weapon-specific inputs)

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag")) // MetaData, will filter out all other tags taht aren't set as "InputTag"
	TArray<FWarriorHeroAbilitySet> DefaultWeaponAbilities;
};


