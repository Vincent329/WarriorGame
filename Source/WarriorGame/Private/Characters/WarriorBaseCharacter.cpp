// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorBaseCharacter.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h" // paste the header here as we need to utilize the classes here
#include "AbilitySystem/WarriorAttributeSet.h"

// Sets default values
AWarriorBaseCharacter::AWarriorBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false; // some VFX will affect the ground.  This will make it so that decals will only affect environments and not the character

	WarriorAbilitySystemComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>(TEXT("WarriorAbilitySystemComponent"));
	WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("WarriorAttributeSet"));

}

UAbilitySystemComponent* AWarriorBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent(); // we're merely going to return our ability system component
}

void AWarriorBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// if the ability system component is valid,
	if (WarriorAbilitySystemComponent)
	{
		// For the InitAbilityActorInfo function, the following arguments are as follows
		// Owner Actor: The actor that owns the Ability System Component
		// Active Actor: An actor in the game world
		// In this case, for the character, both arguments are one and the same
		WarriorAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}



