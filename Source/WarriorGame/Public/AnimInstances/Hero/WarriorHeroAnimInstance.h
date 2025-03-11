// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"

class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override; // override Initialize Animation function from the base AnimInstance class
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;  // override thread safe update animation function.  Use Thread Safe to have this run on a separate thread, not game thread

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|References")
	AWarriorHeroCharacter* OwningHeroCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool b_ShouldEnterRelaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData") // we want to edit the threshold timer in editor
	float f_EnterRelaxThreshold = 5.f;				// should we idle for more than 5 seconds, we are in relax stance

	float f_IdleElapsedTime = 0.f;						// keeping track of the Idle Elapsed Time

};
