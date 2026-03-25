// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorHeroGameplayAbility.generated.h"

class AWarriorHeroCharacter;
class AWarriorHeroController;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Warrior | Ability")
	AWarriorHeroCharacter* GetHeroCharacterFromActorInfo(); // return our hero character

	UFUNCTION(BlueprintPure, Category = "Warrior | Ability")
	AWarriorHeroController* GetHeroControllerFromActorInfo(); // return our hero controller

	UFUNCTION(BlueprintPure, Category = "Warrior | Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior | Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

private:
	TWeakObjectPtr< AWarriorHeroCharacter> CachedWarriorHeroCharacter;	// a Smart pointer type in Unreal, effective if the reference does not need to be a UPROPERTY.  
																		// Simply holds a reference to the object, doesn't keep the object it points to alive
																		// doesn't increaese the reference counting.  This type is used in Unreal a lot -> how values are cached in AbilityActorInfo
																		// But you'll never be sure if the reference is valid, must always check
									
	TWeakObjectPtr< AWarriorHeroController> CachedWarriorHeroController;	// Same Rules as above, but caching the reference of the hero controller   
	TWeakObjectPtr< AWarriorHeroController> CachedHeroCombatCompponent;	// Same Rules as above, but caching the reference of the hero combat component   


};
