// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorAnimInstance.h"
#include "WarriorCharacterAnimInstance.generated.h"

class AWarriorBaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class WARRIORGAME_API UWarriorCharacterAnimInstance : public UWarriorAnimInstance
{
	GENERATED_BODY()
public:

	// no need to call super in any of these classes
	virtual void NativeInitializeAnimation() override; // override Initialize Animation function from the base AnimInstance class
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;  // override thread safe update animation function.  Use Thread Safe to have this run on a separate thread, not game thread
																				// acts similarly to our tick function, but works on worker thread, not game thread
																				// optimized so that our animation blueprints can avoid bottlenecks
protected:
	UPROPERTY()
	AWarriorBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float f_GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool b_HasAcceleration;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool b_IsOnGround;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool b_IsFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool b_DidJump = false;


};
