// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
	/** Input Tags 
	to declare the gameplay tag, need to add in macro with the following format: PROJECTNAME_API
	use our project name WARRIORGAME in this case
	**/

	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);

	//---- Need to see if we need to extend these tags to other weapons
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipWeapon);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipWeapon);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Sword);

	/* Player Tags */
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause); // the hit pause ability

	// REMEMBER THAT EVENT TAGS AND ABILITY TAGS ARE DIFFERENT.  ABILITY IS WHEN WE PRESS, ABILITY IS FOR THE EVENTS AND ANIMATIONS THAT PROCEED
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause); // event for hit pause

	/* Status Tags */
	// NOTE: Perhaps extend this functionality to when there's a unique animation for any attack in the route
	// MAYBE ALSO: Extend for directional attack inputs
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_AttackCancel);

	/* Enemy Tags */
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee); // define these abilities later in the course
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	/* Attack Type Tags */
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	/* Shared Tags */
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact); // both player and enemy will hit each other

	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);


	
	// NEXT STEP, define in cpp file

}