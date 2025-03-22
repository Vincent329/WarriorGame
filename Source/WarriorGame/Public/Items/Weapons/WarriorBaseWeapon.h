// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorBaseWeapon.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class WARRIORGAME_API AWarriorBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarriorBaseWeapon();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UBoxComponent* WeaponCollider;

public:
	FORCEINLINE UStaticMeshComponent* GetWeaponMesh () { return WeaponMesh; }
	FORCEINLINE UBoxComponent* GetWeaponCollider () { return WeaponCollider; }
};
