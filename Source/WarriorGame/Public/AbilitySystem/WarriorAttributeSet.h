// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorAttributeSet.generated.h"

// these defines act as a getter and setter for any gameplay attribute properties, much more useful than regular getters and setters
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UWarriorAttributeSet();

	// can find this in the Attribute Set header
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth; 	
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth; 	
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxHealth)


	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData CurrentRage; 	
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, CurrentRage)

	UPROPERTY(BlueprintReadOnly, Category = "Rage")
	FGameplayAttributeData MaxRage; 	
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, MaxRage)


	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower; 	
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, AttackPower)

		UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower; 	
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DefensePower)

	// placeholder property for 
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UWarriorAttributeSet, DamageTaken)
};
