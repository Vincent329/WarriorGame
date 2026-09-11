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

void UWarriorWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		// creating a helper function that will help us retrieve the pawn's UI component
		// if calling manually, this enemyUIcomponent must be valid
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();
		checkf(EnemyUIComponent, TEXT("Failed to extract an Enemy UI Component from %s"), *OwningEnemyActor->GetActorNameOrLabel());
		
		// Entry point to binding delegates, like the owning UI Hero.
		// We call the event upon initialization, and we're filling out the logic in the Blueprint
		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}

}
