// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarriorDebugHelper.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Components/CameraComponent.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorHeroCharacter.generated.h"

// forward declaration of the Spring Arm and Camera Components
// this will help speed up compile times
class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class WARRIORGAME_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

public:
	AWarriorHeroCharacter();
	
protected:
	virtual void BeginPlay() override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	USkeletalMeshComponent* SkeletalMesh;
#pragma endregion
};
