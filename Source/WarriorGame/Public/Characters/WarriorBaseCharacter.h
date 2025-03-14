// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "WarriorBaseCharacter.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorAttributeSet;

UCLASS()
class WARRIORGAME_API AWarriorBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarriorBaseCharacter();

	//~Begin IAbilitySystemInterface Interface

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End IAbilitySystemInterface Interface

protected:
	//---------- For Character Inherited classes, it's good practice to dscomment the beginning and ending of the APawn interface
	
	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface 


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	UWarriorAbilitySystemComponent* WarriorAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	UWarriorAttributeSet* WarriorAttributeSet;

public:
	// public getters will give us access to these components in C++
	FORCEINLINE UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const { return WarriorAbilitySystemComponent;};
	FORCEINLINE UWarriorAttributeSet* GetUWarriorAttributeSet() const {return WarriorAttributeSet;};
	
};
