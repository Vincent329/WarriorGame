// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WarriorBaseWeapon.h"
#include "Components/BoxComponent.h"
#include "WarriorDebugHelper.h"

// Sets default values
AWarriorBaseWeapon::AWarriorBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollider->SetupAttachment(GetRootComponent());
	WeaponCollider->SetBoxExtent(FVector(20.0f));
	WeaponCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set Delegates for the On Collision enter and exit overlap components from the Primitive Component 
	WeaponCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBeginOverlap);
	WeaponCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionEndOverlap);

}

void AWarriorBaseWeapon::OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		// 
		if (WeaponOwningPawn != HitPawn)
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}

		// implement the hit check
	}
}

void AWarriorBaseWeapon::OnCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		// 
		if (WeaponOwningPawn != HitPawn)
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}

		// implement the hit check
	}
}
	

