// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WarriorWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

void UWarriorWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// from the User Widget Parent Class
	if (IPawnUIInterface *PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			// later in our widget blueprint, we'll override this function to finish the function binding, essentially we're gonna be binding the function capabilities
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent); 
		}
	}
}
