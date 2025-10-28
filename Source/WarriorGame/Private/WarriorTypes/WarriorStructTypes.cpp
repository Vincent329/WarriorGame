// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorTypes/WarriorStructTypes.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

bool FWarriorHeroAbilitySet::IsValid() const {
	return InputTag.IsValid() && AbilityToGrant; // checking if there's a valid tag and if the Ability is valid
}