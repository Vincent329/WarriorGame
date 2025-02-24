// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
	/** Input Tags 
	to declare the gameplay tag, need to add in macro with the following format: PROJECTNAME_API
	use our project name WARRIORGAME in this case
	**/

	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	WARRIORGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)
	// NEXT STEP, define in cpp file

}