// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class WARRIORGAME_API AWarriorEnemyCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()
	
public:
	AWarriorEnemyCharacter();

private:
	void InitEnemyStartUpData();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface private:

public:

	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const{ return EnemyCombatComponent;}
};
