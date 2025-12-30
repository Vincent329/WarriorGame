// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarriorDebugHelper.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Components/CameraComponent.h"
#include "Characters/WarriorBaseCharacter.h"
#include "GameplayTagContainer.h"
#include "WarriorHeroCharacter.generated.h"

// forward declaration of the Spring Arm and Camera Components
// this will help speed up compile times if we use forward declaration over header file includes
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig; // reference the input config asset, necessary for input binding custom inputs
struct FInputActionValue;	// forward declaring a struct
class UHeroCombatComponent;
class UAnimMontage;

/**
 * 
 */
UCLASS()
class WARRIORGAME_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

public:
	AWarriorHeroCharacter();
	
protected:


	// we are overriding the input  component class from the base character header
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	// to try and test that the functions we made in the base character class work, we'll override them here
	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface private:

#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;
#pragma endregion

#pragma region Inputs
	// something we'll assign in editor later
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue); // since we are using the const reference input, simple forward dec
	void Input_Look(const FInputActionValue& InputActionValue); // since we are using the const reference input, simple forward dec
	void Input_Jump(const FInputActionValue& InputActionValue); // since we are using the const reference input, simple forward dec
	void Input_StopJump(const FInputActionValue& InputActionValue); // since we are using the const reference input, simple forward dec
	
	//----------- NOTE: FOR ANY ABILITIES THAT WE'RE ESTABLISHING VIA THE GAMEPLAY ABILITY SYSTEM, THESE FUNCTIONS WILL HANDbLE IT -----------------
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
#pragma endregion

#pragma region Montages
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* JumpAnim;

public:
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent  () const { return HeroCombatComponent; }
};
