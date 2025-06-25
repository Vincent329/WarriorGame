// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UWarriorGameplayAbility;
class UWarriorAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class WARRIORGAME_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()


public:
	// ApplyLevel, this refers to the difficulty level we put in our game.  Can be established in the Main Menu
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1); 
	
protected:

	// TSubclassof provides a safety net in case the casting goes wrong
	// If there's an ability that needs to activated right after it's given, we place it in this array
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ActivateOnGivenAbilities;
	
	// Abilities that are reactive, such as on hit or on death in cerrtain 
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>> InAbilitiesToGive, UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

};
