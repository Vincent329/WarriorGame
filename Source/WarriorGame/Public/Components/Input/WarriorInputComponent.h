// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	// Custom binding input action function
	// when we pass in an Input Config Data Asset, it'll run through the input actions that are in the data set, if the tag set in code matches the one in the asset, we bind the appropriate function
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject,  CallbackFunc func);
	
};

template<class UserObject, typename CallbackFunc>
inline void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	//check(InInputConfig); //check if the InInputConfig pointer is valid
	checkf(InInputConfig, TEXT("Input config data asset is null, cannot proceed with the binding")); //check if the InInputConfig pointer is valid, 2nd method
	
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag)) // check if the input action is valid from the Data Asset, defined in that DataAsset_InputConfig class)
	{
		BindAction(FoundAction,TriggerEvent, ContextObject, Func);
	}

}
