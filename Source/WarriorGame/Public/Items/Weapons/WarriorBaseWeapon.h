// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorBaseWeapon.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

// declare a one parameter delegate to pass in an actor
DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

UCLASS()
class WARRIORGAME_API AWarriorBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarriorBaseWeapon();

	// On the Pawn Combat Component, make sure that functions are bound to these delegates
	FOnTargetInteractedDelegate OnWeaponHitTarget; // Beginning overlap
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget; // Ending overlap

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UBoxComponent* WeaponCollider;

	UFUNCTION()
	virtual void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh () { return WeaponMesh; }
	FORCEINLINE UBoxComponent* GetWeaponCollider () { return WeaponCollider; }
};
