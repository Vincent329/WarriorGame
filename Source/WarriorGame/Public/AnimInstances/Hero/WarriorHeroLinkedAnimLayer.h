// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorAnimInstance.h"
#include "WarriorHeroLinkedAnimLayer.generated.h"

class UWarriorHeroAnimInstance;

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorHeroLinkedAnimLayer : public UWarriorAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe)) // meta specifier for Thread Safe becuase we're going use this function for property access
	UWarriorHeroAnimInstance* GetHeroAnimInstance() const; // When creating this way, this will expse our Anim Instance into our property access
};
