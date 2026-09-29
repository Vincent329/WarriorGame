// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarriorAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class WARRIORGAME_API AWarriorAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
	AWarriorAIController(const FObjectInitializer& ObjectInitializer);

	// -- Begin IGenericTeamAgentInterface Interface --
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const;
	// -- End IGenericTeamAgentInterface Interface --

	protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus AIStimulus);


};
