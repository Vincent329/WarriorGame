// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "WarriorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;
};
