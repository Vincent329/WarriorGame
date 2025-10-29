// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorTypes/WarriorStructTypes.h" // to get the warrior ability sets struct
#include "WarriorAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);


	//REMINDER: if const Tarray, then it should always be a reference or a pointer, since with a reference, it'll actually save all the values you pass in, directly modifying the parameter
	UFUNCTION(BlueprintCallable, Category = "Warrior | Ability", meta = (ApplyLevel = "1")) // for meta data, can apply metadata
	void GrantHeroWeaponAbilities(const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandle); 

	
};
