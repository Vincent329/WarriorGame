// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnComponentExtensionBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARRIORGAME_API UPawnComponentExtensionBase : public UActorComponent
{
	GENERATED_BODY()

protected:

	/* ------------ Returning an Owning Pawn -------------

	If we need to get a specific type of APawn, or get the Player and enemy pawns specifically, we can use these helper functions */

	// this function will help return the class we want regardless of whatever owner it's attached to
	// hero or enemy character
	template<class T>
	T* GetOwningPawn() const
	{
		// Safeguard gheck here for the static assert. If we cast to something like AController, it'll return this error message
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter get GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner()); // if casting fails, it'll crash
	}

	// no specific type
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' template parameter must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}



};
