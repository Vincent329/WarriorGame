// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UEnemyUIComponent;
/**
 * 
 */
UCLASS()
class WARRIORGAME_API AWarriorEnemyCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()
	
public:
	AWarriorEnemyCharacter();

	// ~ Begin IPawnCombatInterface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	// ~ End IPawnCombatInterface
	// 
	// ~ Begin IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override; // =0 means it's a pure Virtual function, so you have to define this in the base classes
	// ~ End IPawnUIInterface

private:
	void InitEnemyStartUpData();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface private:

public:

	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const{ return EnemyCombatComponent;}
};
