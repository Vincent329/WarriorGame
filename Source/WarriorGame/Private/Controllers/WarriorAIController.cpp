// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WarriorAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "WarriorDebugHelper.h"


AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{


	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true; // detect anyone that isn't a team player
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->SightRadius = 5000.f;
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f; // detection angle

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);
	
	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

	// if the other team agent isn't equal to this controller's team ID, then we can assume it's hostile
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return  ETeamAttitude::Friendly;

}

void AWarriorAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		// Viable variables that can alter the effectiveness of the Crowd Avoidance
		// 1) SetCrowdSimulationState(ECrowdSimulationState enum)	
		// 2) SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality enum)
		// if Detour Avoidance is enabled or disabled, we're going to set this
		// 
		//
		// Crowd Avoidance Quality Enums: Low, Medium, High, Good
		//
		// CrowdComp->SetAvoidanceGroup(1);
		// CrowdComp->SetGroupsToAvoid(1);
		//
		CrowdComp->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidanceQuality)
		{
			case 1:	CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);	break;
			case 2: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);	break;
			case 3: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);	break;
			case 4: CrowdComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);	break;
			default:
				break;
		}

		CrowdComp->SetAvoidanceGroup(1); // we pass in the Team ID in the avoidance groups
		CrowdComp->SetGroupsToAvoid(1);
		CrowdComp->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}

// we need to store the Actor Parameter as our Target Actor Key in the Blueprint
void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus AIStimulus)
{
	if (AIStimulus.WasSuccessfullySensed() && Actor)
	{
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			// MAKE SURE that the key name is the exact same as the Blackboard Asset. The Blackboard will immmediately pick up the other actor
			BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor); 
		}
	}
}


