// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag; // if you find a squiggly line, you can press F12 to go to the declaration of the data type if it exists and find the include directories needed

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWarriorGameplayAbility> AbilityToGrant;

	bool IsValid() const; // we want to check if the Ability to grant
};

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray< FWarriorHeroAbilitySet> HeroStartUpAbilitySets;

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;


};
