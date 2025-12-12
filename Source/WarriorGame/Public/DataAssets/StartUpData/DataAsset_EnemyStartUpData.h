// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "WarriorTypes/WarriorStructTypes.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UWarriorEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class WARRIORGAME_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<TSubclassOf<UWarriorEnemyGameplayAbility>> EnemyCombatAbilities;

public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

	
};
