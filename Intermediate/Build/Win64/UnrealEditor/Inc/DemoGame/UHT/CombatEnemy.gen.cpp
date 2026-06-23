// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatEnemy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatEnemy() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidgetComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemy(ETypeConstructPhase);
DEMOGAME_API UFunction* Z_Construct_UDelegateFunction_DemoGame_OnEnemyDied__DelegateSignature(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatAttacker(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatDamageable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemy(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatLifeBar(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Delegate FOnEnemyDied **********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UDelegateFunction_DemoGame_OnEnemyDied__DelegateSignature_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enemy died delegate */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enemy died delegate" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Delegate FOnEnemyDied constinit property declarations **************************
// ********** End Delegate FOnEnemyDied constinit property declarations ****************************
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FDelegateFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame, nullptr, "OnEnemyDied__DelegateSignature", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UDelegateFunction_DemoGame_OnEnemyDied__DelegateSignature(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Delegate FOnEnemyDied ************************************************************

// ********** Begin Class ACombatEnemy Function CheckChargedAttack *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatEnemy_CheckChargedAttack_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs a charged attack's check to loop the charge animation */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs a charged attack's check to loop the charge animation" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CheckChargedAttack constinit property declarations ********************
// ********** End Function CheckChargedAttack constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatEnemy, nullptr, "CheckChargedAttack", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatEnemy_CheckChargedAttack(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatEnemy::execCheckChargedAttack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckChargedAttack();
	P_NATIVE_END;
}
// ********** End Class ACombatEnemy Function CheckChargedAttack ***********************************

// ********** Begin Class ACombatEnemy Function CheckCombo *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatEnemy_CheckCombo_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs a combo attack's check to continue the string */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs a combo attack's check to continue the string" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CheckCombo constinit property declarations ****************************
// ********** End Function CheckCombo constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatEnemy, nullptr, "CheckCombo", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatEnemy_CheckCombo(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatEnemy::execCheckCombo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckCombo();
	P_NATIVE_END;
}
// ********** End Class ACombatEnemy Function CheckCombo *******************************************

// ********** Begin Class ACombatEnemy Function ReceivedDamage *************************************
struct CombatEnemy_eventReceivedDamage_Parms
{
	float Damage;
	FVector ImpactPoint;
	FVector DamageDirection;
};
static FName NAME_ACombatEnemy_ReceivedDamage = FName(TEXT("ReceivedDamage"));
void ACombatEnemy::ReceivedDamage(float Damage, FVector const& ImpactPoint, FVector const& DamageDirection)
{
	CombatEnemy_eventReceivedDamage_Parms Parms;
	Parms.Damage=Damage;
	Parms.ImpactPoint=ImpactPoint;
	Parms.DamageDirection=DamageDirection;
	UFunction* Func = FindFunctionChecked(NAME_ACombatEnemy_ReceivedDamage);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatEnemy_ReceivedDamage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to play damage received effects */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to play damage received effects" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactPoint_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageDirection_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function ReceivedDamage constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ImpactPoint;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DamageDirection;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ReceivedDamage constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ReceivedDamage Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemy_eventReceivedDamage_Parms, Damage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ImpactPoint = { "ImpactPoint", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemy_eventReceivedDamage_Parms, ImpactPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactPoint_MetaData), NewProp_ImpactPoint_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_DamageDirection = { "DamageDirection", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemy_eventReceivedDamage_Parms, DamageDirection), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageDirection_MetaData), NewProp_DamageDirection_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Damage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DamageDirection,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ReceivedDamage Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatEnemy, nullptr, "ReceivedDamage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<CombatEnemy_eventReceivedDamage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(CombatEnemy_eventReceivedDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatEnemy_ReceivedDamage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ACombatEnemy Function ReceivedDamage ***************************************

// ********** Begin Class ACombatEnemy *************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ACombatEnemy_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  An AI-controlled character with combat capabilities.\n *  Its bundled AI Controller runs logic through StateTree\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Combat/AI/CombatEnemy.h" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An AI-controlled character with combat capabilities.\nIts bundled AI Controller runs logic through StateTree" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifeBar_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Life bar widget component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Life bar widget component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHP_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of HP the character will have on respawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of HP the character will have on respawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "Damage" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current amount of HP the character has */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current amount of HP the character has" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PelvisBoneName_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the pelvis bone, for damage ragdoll physics */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the pelvis bone, for damage ragdoll physics" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifeBarWidget_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pointer to the life bar widget */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pointer to the life bar widget" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeTraceDistance_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "500" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance ahead of the character that melee attack sphere collision traces will extend */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance ahead of the character that melee attack sphere collision traces will extend" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeTraceRadius_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "500" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the sphere trace for melee attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the sphere trace for melee attacks" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeDamage_MetaData[] = {
		{ "Category", "Melee Attack|Damage" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of damage a melee attack will deal */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of damage a melee attack will deal" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeKnockbackImpulse_MetaData[] = {
		{ "Category", "Melee Attack|Damage" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of knockback impulse a melee attack will apply */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of knockback impulse a melee attack will apply" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeLaunchImpulse_MetaData[] = {
		{ "Category", "Melee Attack|Damage" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of upwards impulse a melee attack will apply */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of upwards impulse a melee attack will apply" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboAttackMontage_MetaData[] = {
		{ "Category", "Melee Attack|Combo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AnimMontage that will play for combo attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage that will play for combo attacks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboSectionNames_MetaData[] = {
		{ "Category", "Melee Attack|Combo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Names of the AnimMontage sections that correspond to each stage of the combo attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Names of the AnimMontage sections that correspond to each stage of the combo attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargedAttackMontage_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AnimMontage that will play for charged attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage that will play for charged attacks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargeLoopSection_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the AnimMontage section that corresponds to the charge loop */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the AnimMontage section that corresponds to the charge loop" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargeAttackSection_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the AnimMontage section that corresponds to the attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the AnimMontage section that corresponds to the attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinChargeLoops_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
		{ "ClampMax", "20" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum number of charge animation loops that will be played by the AI */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum number of charge animation loops that will be played by the AI" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxChargeLoops_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
		{ "ClampMax", "20" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum number of charge animation loops that will be played by the AI */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum number of charge animation loops that will be played by the AI" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathRemovalTime_MetaData[] = {
		{ "Category", "Death" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before removing this character from the level after it dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before removing this character from the level after it dies" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnEnemyDied_MetaData[] = {
		{ "Category", "Events" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Enemy died delegate. Allows external subscribers to respond to enemy death */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Enemy died delegate. Allows external subscribers to respond to enemy death" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ACombatEnemy constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LifeBar;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHP;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PelvisBoneName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LifeBarWidget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeTraceRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeDamage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeKnockbackImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeLaunchImpulse;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ComboAttackMontage;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ComboSectionNames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ComboSectionNames;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChargedAttackMontage;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ChargeLoopSection;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ChargeAttackSection;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MinChargeLoops;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxChargeLoops;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathRemovalTime;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnEnemyDied;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ACombatEnemy constinit property declarations *******************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CheckChargedAttack"), .Pointer = &ACombatEnemy::execCheckChargedAttack },
		{ .NameUTF8 = UTF8TEXT("CheckCombo"), .Pointer = &ACombatEnemy::execCheckCombo },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatEnemy_CheckChargedAttack, "CheckChargedAttack" }, // 026502941958a4a632b0aec9cf3fad04dd62581d
		{ &Z_Construct_UFunction_ACombatEnemy_CheckCombo, "CheckCombo" }, // dcc501bf56fb77cd65a1da80a6044330eb31f208
		{ &Z_Construct_UFunction_ACombatEnemy_ReceivedDamage, "ReceivedDamage" }, // 1de25fa7b99ab38ef55d1e8d2f970846636299eb
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatEnemy>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ACombatEnemy Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LifeBar = { "LifeBar", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, LifeBar), Z_Construct_UClass_UWidgetComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBar_MetaData), NewProp_LifeBar_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxHP = { "MaxHP", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MaxHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHP_MetaData), NewProp_MaxHP_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CurrentHP = { "CurrentHP", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_PelvisBoneName = { "PelvisBoneName", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, PelvisBoneName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PelvisBoneName_MetaData), NewProp_PelvisBoneName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LifeBarWidget = { "LifeBarWidget", nullptr, (EPropertyFlags)0x0020080000080009, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, LifeBarWidget), Z_Construct_UClass_UCombatLifeBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBarWidget_MetaData), NewProp_LifeBarWidget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeTraceDistance = { "MeleeTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MeleeTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeTraceDistance_MetaData), NewProp_MeleeTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeTraceRadius = { "MeleeTraceRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MeleeTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeTraceRadius_MetaData), NewProp_MeleeTraceRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeDamage = { "MeleeDamage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MeleeDamage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeDamage_MetaData), NewProp_MeleeDamage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeKnockbackImpulse = { "MeleeKnockbackImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MeleeKnockbackImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeKnockbackImpulse_MetaData), NewProp_MeleeKnockbackImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeLaunchImpulse = { "MeleeLaunchImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MeleeLaunchImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeLaunchImpulse_MetaData), NewProp_MeleeLaunchImpulse_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ComboAttackMontage = { "ComboAttackMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, ComboAttackMontage), Z_Construct_UClass_UAnimMontage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboAttackMontage_MetaData), NewProp_ComboAttackMontage_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ComboSectionNames_Inner = { "ComboSectionNames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ComboSectionNames = { "ComboSectionNames", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, ComboSectionNames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboSectionNames_MetaData), NewProp_ComboSectionNames_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ChargedAttackMontage = { "ChargedAttackMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, ChargedAttackMontage), Z_Construct_UClass_UAnimMontage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargedAttackMontage_MetaData), NewProp_ChargedAttackMontage_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ChargeLoopSection = { "ChargeLoopSection", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, ChargeLoopSection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargeLoopSection_MetaData), NewProp_ChargeLoopSection_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ChargeAttackSection = { "ChargeAttackSection", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, ChargeAttackSection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargeAttackSection_MetaData), NewProp_ChargeAttackSection_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MinChargeLoops = { "MinChargeLoops", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MinChargeLoops), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinChargeLoops_MetaData), NewProp_MinChargeLoops_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_MaxChargeLoops = { "MaxChargeLoops", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, MaxChargeLoops), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxChargeLoops_MetaData), NewProp_MaxChargeLoops_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeathRemovalTime = { "DeathRemovalTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, DeathRemovalTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathRemovalTime_MetaData), NewProp_DeathRemovalTime_MetaData) };
const UECodeGen_Private::FMulticastDelegatePropertyParams UHT_STATICS::NewProp_OnEnemyDied = { "OnEnemyDied", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemy, OnEnemyDied), Z_Construct_UDelegateFunction_DemoGame_OnEnemyDied__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnEnemyDied_MetaData), NewProp_OnEnemyDied_MetaData) }; // 75241870b6e67bf36c249f3dee53315948a6595d
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LifeBar,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PelvisBoneName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LifeBarWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeTraceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeKnockbackImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeLaunchImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboAttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboSectionNames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboSectionNames,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChargedAttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChargeLoopSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChargeAttackSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MinChargeLoops,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxChargeLoops,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeathRemovalTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OnEnemyDied,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ACombatEnemy Property Definitions ******************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ACharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatAttacker, (int32)VTABLE_OFFSET(ACombatEnemy, ICombatAttacker), false },  // a9476cba592e946f33d8cdd21adabb99af57975c
	{ Z_Construct_UClass_UCombatDamageable, (int32)VTABLE_OFFSET(ACombatEnemy, ICombatDamageable), false },  // 7a4b5a8e7c3a75940e8ea3985c2adf6d465912d0
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ACombatEnemy,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ACombatEnemy_StaticRegisterNativesACombatEnemy()
{
	UClass* Class = ACombatEnemy::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatEnemy;
UClass* Z_Construct_UClass_ACombatEnemy(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ACombatEnemy;
		if (!Z_Registration_Info_UClass_ACombatEnemy.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatEnemy"),
				Z_Registration_Info_UClass_ACombatEnemy.InnerSingleton,
				ACombatEnemy_StaticRegisterNativesACombatEnemy,
				DataSizeOf<TClass>(),
				alignof(TClass),
				TClass::StaticClassFlags,
				TClass::StaticClassCastFlags(),
				TClass::StaticConfigName(),
				(UClass::ClassConstructorType)InternalConstructor<TClass>,
				(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
				UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
				&TClass::Super::StaticClass,
				&TClass::WithinClass::StaticClass
			);
		}
		return Z_Registration_Info_UClass_ACombatEnemy.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ACombatEnemy.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatEnemy.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatEnemy.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ACombatEnemy);
ACombatEnemy::~ACombatEnemy() {}
// ********** End Class ACombatEnemy ***************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatEnemy, TEXT("ACombatEnemy"), &Z_Registration_Info_UClass_ACombatEnemy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatEnemy), 626487834U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h__Script_DemoGame_b9d03d57ad95e09549c9d349b926cd155ca781f6{
	TEXT("/Script/DemoGame"),
	UHT_STATICS::ClassInfo, UE_ARRAY_COUNT(UHT_STATICS::ClassInfo),
	nullptr, 0,
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
