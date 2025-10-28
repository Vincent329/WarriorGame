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
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Attack);

	//---- Need to see if we need to extend these tags to other weapons
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipWeapon);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipWeapon);

	/* Player Tags */
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Sword);
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Sword);

	
	// NEXT STEP, define in cpp file

}