// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WarriorBaseWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWarriorBaseWeapon::AWarriorBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollider->SetupAttachment(GetRootComponent());
	WeaponCollider->SetBoxExtent(FVector(20.0f);
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
	

