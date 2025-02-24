// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag)
{
	for (const FWarriorInputActionConfig& InputActionConfig : NativeInputActions) // foreach loop going through the different input action configs
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction) // if the input action exists with the input tag
		{
			return InputActionConfig.InputAction;
		} 
	}

	return nullptr;
}
