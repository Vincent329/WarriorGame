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
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Sword);

	// REMEMBER THAT EVENT TAGS AND ABILITY TAGS ARE DIFFERENT.  INPUT IS WHEN WE PRESS, ABILITY IS FOR THE EVENTS AND ANIMATIONS THAT PROCEED
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_AttackCancel);


	/* Enemy Tags */
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	/* Status Tags */
	// NOTE: Perhaps extend this functionality to when there's a unique animation for any attack in the route
	// MAYBE ALSO: Extend for directional attack inputs
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);


	
	// NEXT STEP, define in cpp file

}