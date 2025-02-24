// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction; // forward declaration of Input Actions
class UInputMappingContext; // forward declaration of Input Mapping Contexts

// Struct used to mapp input tags to input actions
USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
	GENERATED_BODY() // make sure this macro is there or else we won't compile 

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag; // if you find a squiggly line, you can press F12 to go to the declaration of the data type if it exists nad find the include directories needed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction; // if you find a squiggly line, you can press F12 to go to the declaration of the data type if it exists nad find the include directories needed
								// WEIRD... had to re-order Enhanced input in Build.cs to fix the external error

};

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
	// fill any variables we need
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputAction"))	// variable can be anything we defined inside the input action config struct,
	TArray<FWarriorInputActionConfig> NativeInputActions;									// using the name Input Action for the rows inside this array

	// helper function to help us find input actions by tag
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag);

};
