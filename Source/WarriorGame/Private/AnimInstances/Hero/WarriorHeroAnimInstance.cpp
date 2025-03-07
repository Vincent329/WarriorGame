// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"
#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework\CharacterMovementComponent.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());

	// nativeinitialize animation is called in the editor
	// can't use check macro here
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	f_GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	b_HasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.0f; // essentially returning the magnitude of the acceleration (2D vector magnitude if we're just getting the lateral accelaration).
}
