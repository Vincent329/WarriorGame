// Fill out your copyright notice in the Description page of Project Settings.


// GEExecCalc_DealDamage
// Custom Calculation Class that takes our attribute set
// and upon the calling of the gameplay effect, we then execute the following attack calculation
//

#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/WarriorAttributeSet.h" // needs this for Find Field Checked
#include "WarriorGameplayTags.h"
#include "WarriorDebugHelper.h"

// struct for the fast way of doing htis
struct FWarriorDamageCapture {
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower) // under the hood. it's the same as creating the FProperty Pointer
		DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower) //
		DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken) //


	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, AttackPower, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DefensePower, Target, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet, DamageTaken, Target, false)
	}
};

// Static getter class for the damage capture
static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{

// ---- Slow way of doing this ---------
// research what FProperty does
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UWarriorAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UWarriorAttribtueSet, AttackPower)
	//);

	//FGameplayEffectAttributeCaptureDefinition AttackPowerDefinitionCaptureDefinition( //1. the attack property, 2. the source of the property, 3. whether or not the we want to capture this attribute
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source, // The source that's applying this gameplay effect
	//	false// true means capturing once effect is created, false means capturing once the effect is applied
	//);

	//RelevantAttributesToCapture.Add(AttackPowerDefinitionCaptureDefinition);
 //
// ---- Fast way of doing this ---------

	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef); // Refresher for what this does.  This is reflecting data from the Attribute Set that we created
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef); // Refresher for what this does.  This is reflecting data from the Attribute Set that we created
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageTakenDef); // Refresher for what this does.  This is reflecting data from the Attribute Set that we created

	// next lecture, we'll dictate how to use these captured variables and extract the values needed
}

// for the execution, we take in a parameter for Execution parameters, and we have a custom output that will let us connect to other nodes. (This effect is placed in GE_Shared_DealDamage)
void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// for this we're essentially ret
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec.GetContext().GetSourceObject();	// context handle, we can retrieve the source object, or the ability that created this effect spec, or the Instigator, or EffectCause, we set these when we constructed the effect spec handle
												// refer to the Hero Gameplay Ability class (Make Hero Damage Effect Spec Handle)
												// we can choose what we can do with the context based on what 
												
	// get a hold of all the relevant values for calculating final damage
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	//Debug::Print(TEXT("SourceAttackPower -> "), SourceAttackPower);

	// capture definition - which attribute value we're trying to get (AttackPower/DefensePowerdef)
	// Evaluate Parameters, Agregator tags
	// Damage Value - create it above, contains the actual value
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	float BaseDamage = 0.f;
	int32 UsedLightAttackComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	
	// TMap that we place the elements into inside of our helper function
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			//Debug::Print(TEXT("BaseDamage -> "), BaseDamage);
			

		}
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedLightAttackComboCount -> "), UsedLightAttackComboCount);

		}
		if (TagMagnitude.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
			//Debug::Print(TEXT("UsedHeavyAttackComboCount -> "), UsedHeavyAttackComboCount);

		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);
	// Debug::Print(TEXT("TargetDefensePower -> "), TargetDefensePower);


	// enemies will not use the light and heavy attack combo count, unless you decide for them to necessitate it

	if (UsedLightAttackComboCount != 0)
	{
		// Logic:  the first hit of the light attack will be unscaled, then for every successive attack it's going to slightly increase in scaling
		// meaning the longer the combo goes, the more attack strength it will have

		// ------------- CONSIDER: if each attack should have its own dedicated attack strength rather than scaled
		const float DamageIncreasePercentLight = (UsedLightAttackComboCount -1) * 0.05f + 1.0f;
		BaseDamage *= DamageIncreasePercentLight;
		//Debug::Print(TEXT("ScaledBaseDamageLight -> "), BaseDamage);

	}

	if (UsedHeavyAttackComboCount != 0)
	{
		// scale the heavy attack first attack right out of the gate
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.0f;
		BaseDamage *= DamageIncreasePercentHeavy;
		//Debug::Print(TEXT("ScaledBaseDamageHeavy -> "), BaseDamage);


	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower; // simple way to calculate the final damage ,
	//Debug::Print(TEXT("FinalDamageDone -> "), FinalDamageDone);

	if (FinalDamageDone > 0.0f)
	{
		// using a placeholder value to alter first, then that placeholder value will go into the current health
		// helpful to do any further calculations to the final attribute data if needed
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetWarriorDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
		
		// execution calculation is communicated to the Ability System Component's attribute set

	}

}
