// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WarriorBaseWeapon.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "GameplayAbilitySpecHandle.h"
#include "WarriorHeroWeapon.generated.h"


/**
 * 
 */
UCLASS()
class WARRIORGAME_API AWarriorHeroWeapon : public AWarriorBaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray< FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

private:
	 // Don't need to include the entire WarriorGameplayAbility header, just find the spec handle header file
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;

};
