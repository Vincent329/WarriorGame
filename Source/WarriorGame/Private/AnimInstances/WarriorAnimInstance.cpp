// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WarriorAnimInstance.h"
#include "WarriorFunctionLibrary.h"

bool UWarriorAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWarriorFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	return false;
}
