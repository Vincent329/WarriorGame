// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/WarriorInputComponent.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h" // paste the header here as we need to utilize the classes here
#include "AbilitySystem/WarriorAttributeSet.h" // paste the header here as we need to utilize the classes here

#include "WarriorGameplayTags.h" // get the tags in here


// trick to keep debug underneath all the includes, to help see what classes have the debug helper or not
#include "WarriorDebugHelper.h"

AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent()); // attach this to the root component
	CameraBoom->TargetArmLength = 500.0f;	// Keep the follow camera close to our character, offset to the side on our shoulder
											// This can be customized to our liking so don't need to be too rigid on this
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f); // Camera goes a bit to the right, and raised a bit high
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 100.f;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 100.0f;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Input Config Data Asset is null, forgot to assign valid data asset as input config"));
	
	// Step1:	Get a reference to our Player Controller
	//		-	store this in a local variable first
	APlayerController* PController = GetController<APlayerController>();
	ULocalPlayer* LocalPlayer = PController->GetLocalPlayer(); // We'll get the EnhancedLocalInputSubSystem from this local player
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem =	ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);	// the Subsystem is pointing to the local player's subsystem, 
																					//and this way we can directly add the mapping context to the local player

	UWarriorInputComponent* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);	// by creating a CastChecked, if the player input component is null or if the cast fails
																												// game will crash immediately.  This way we can easily debug and check if Player Input Component is valid
																												// Warrior Input Component will be valid if we pass this check
	
	PController->SetInputMode(FInputModeGameOnly());
	
	// setting up the movemnet
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, /*Create the Callback function, alternatively use &AWarriorHeroCharacter*/&ThisClass::Input_Move);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, /*Create the Callback function, alternatively use &AWarriorHeroCharacter*/&ThisClass::Input_Look);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Jump, ETriggerEvent::Started, this, /*Create the Callback function, alternatively use &AWarriorHeroCharacter*/&ThisClass::Input_Jump);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Jump, ETriggerEvent::Completed, this, /*Create the Callback function, alternatively use &AWarriorHeroCharacter*/&ThisClass::Input_StopJump);


}


void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// if the ability system component is valid,
	if (WarriorAbilitySystemComponent && WarriorAttributeSet)
	{

	// debug string to check if the components made are valid
		const FString ASCText = FString::Printf(TEXT("Owner Actor: %s, Avatar Actor: %s"), *WarriorAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *WarriorAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
		
		Debug::Print(TEXT("Ability System Component Valid. ") + ASCText, FColor::Green);
		Debug::Print(TEXT("Attribute Set Valid. ") + ASCText, FColor::Green);
		

	}
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();	// movement axis on a 2D plane
	const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f); // only account for the yaw of the controller

	// movement logic
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookRotationAxis = InputActionValue.Get<FVector2D>();

	if (LookRotationAxis.X != 0.f)
	{
		AddControllerYawInput(LookRotationAxis.X);
	}
	if (LookRotationAxis.Y != 0.0f)
	{
		AddControllerPitchInput(LookRotationAxis.Y);
	}
}

void AWarriorHeroCharacter::Input_Jump(const FInputActionValue& InputActionValue)
{
	Jump();

}

void AWarriorHeroCharacter::Input_StopJump(const FInputActionValue& InputActionValue)
{
	StopJumping();

}
