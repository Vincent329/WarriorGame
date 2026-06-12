// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponentExtensionBase.h"
#include "PawnUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangedDelegate, float, NewPercent); // any value that gets changed, call this

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UPawnUIComponent : public UPawnComponentExtensionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable) // Blueprint assignable so that in BP, we can call this delegate in 
	FOnPercentChangedDelegate OnCurrentHealthChanged; // 
};
