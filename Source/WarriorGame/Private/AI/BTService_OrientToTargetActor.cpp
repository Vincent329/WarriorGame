// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_OrientToTargetActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_OrientToTargetActor::UBTService_OrientToTargetActor()
{
	NodeName = TEXT("Native Orient Rotation To Target Actor");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	bNotifyTick = true;
	RotationInterpSpeed = 5.f;	
	Interval = 0.f;
	RandomDeviation = 0.f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass()); // limits key tabs that we
}

void UBTService_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	// What we're checking here (if the Blackboard asset is valid, then the key we want to find we wish to resolve and clean up for use in this class)
	// 
	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BBAsset); // dereference the BBAsset to access it
	}
}

FString UBTService_OrientToTargetActor::GetStaticDescription() const
{
	const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();
	// pointers on this FString is interesting
	return FString::Printf(TEXT("Orient Rotation to %s Key %s"), *KeyDescription, *GetStaticServiceDescription());
	
}

void UBTService_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	UObject* ActorObject =	OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject); 

	// get the owning pawn of this service
	APawn* OwningPawn =	OwnerComp.GetAIOwner()->GetPawn();
	if (OwningPawn && TargetActor)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
		const FRotator TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);	
	
		OwningPawn->SetActorRotation(TargetRot);
	}
}
