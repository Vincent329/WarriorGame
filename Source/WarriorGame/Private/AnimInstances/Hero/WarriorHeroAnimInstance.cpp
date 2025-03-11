// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"
#include "Characters/WarriorHeroCharacter.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// we are getting our Owning Character from the parent class, it's just a Base Class
	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AWarriorHeroCharacter>(OwningCharacter); // This is coming from the header, this will be our hero character reference
	}
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (b_HasAcceleration)
	{
		f_IdleElapsedTime = 0.0f;
		b_ShouldEnterRelaxState = false;
		
	}
	else
	{
		f_IdleElapsedTime += DeltaSeconds;
		b_ShouldEnterRelaxState = (f_IdleElapsedTime >= f_EnterRelaxThreshold); // change the relax state to true if elapsed time greater than or equal to the relax threshold
	}
}
