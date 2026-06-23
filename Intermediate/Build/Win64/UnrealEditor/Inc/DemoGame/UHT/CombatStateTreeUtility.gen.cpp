// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatStateTreeUtility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatStateTreeUtility() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeConditionCommonBase(ETypeConstructPhase);
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeTaskCommonBase(ETypeConstructPhase);
AIMODULE_API UClass* Z_Construct_UClass_AAIController(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeAttackInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeChargedAttackTask(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeComboAttackTask(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorTask(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationTask(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeIsInDangerCondition(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeIsInDangerConditionInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemy(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FStateTreeCharacterGroundedConditionInstanceData ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeCharacterGroundedConditionInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeCharacterGroundedConditionInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the FStateTreeCharacterGroundedCondition condition\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the FStateTreeCharacterGroundedCondition condition" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character to check grounded status on */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character to check grounded status on" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bMustBeOnAir_MetaData[] = {
		{ "Category", "Condition" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the condition passes if the character is not grounded instead */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the condition passes if the character is not grounded instead" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeCharacterGroundedConditionInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static void NewProp_bMustBeOnAir_SetBit(void* Obj)
	{
		((FStateTreeCharacterGroundedConditionInstanceData*)Obj)->bMustBeOnAir = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bMustBeOnAir;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeCharacterGroundedConditionInstanceData constinit property declarations 
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeCharacterGroundedConditionInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeCharacterGroundedConditionInstanceData Property Definitions 
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeCharacterGroundedConditionInstanceData, Character), Z_Construct_UClass_ACharacter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bMustBeOnAir = { "bMustBeOnAir", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FStateTreeCharacterGroundedConditionInstanceData), &UHT_STATICS::NewProp_bMustBeOnAir_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bMustBeOnAir_MetaData), NewProp_bMustBeOnAir_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bMustBeOnAir,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeCharacterGroundedConditionInstanceData Property Definitions 
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeCharacterGroundedConditionInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeCharacterGroundedConditionInstanceData>(),
	alignof(FStateTreeCharacterGroundedConditionInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeCharacterGroundedConditionInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeCharacterGroundedConditionInstanceData ********************

// ********** Begin ScriptStruct FStateTreeCharacterGroundedCondition ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeCharacterGroundedCondition>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeCharacterGroundedCondition); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree condition to check if the character is grounded\n */" },
#endif
		{ "DisplayName", "Character is Grounded" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree condition to check if the character is grounded" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeCharacterGroundedCondition constinit property declarations 
// ********** End ScriptStruct FStateTreeCharacterGroundedCondition constinit property declarations 
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeCharacterGroundedCondition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeCharacterGroundedCondition>() == std::is_polymorphic<FStateTreeConditionCommonBase>(), "USTRUCT FStateTreeCharacterGroundedCondition cannot be polymorphic unless super FStateTreeConditionCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeConditionCommonBase,
	&NewStructOps,
	"StateTreeCharacterGroundedCondition",
	nullptr,
	0,
	DataSizeOf<FStateTreeCharacterGroundedCondition>(),
	alignof(FStateTreeCharacterGroundedCondition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeCharacterGroundedCondition"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeCharacterGroundedCondition ********************************

// ********** Begin ScriptStruct FStateTreeIsInDangerConditionInstanceData *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeIsInDangerConditionInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeIsInDangerConditionInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeIsInDangerConditionInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the FStateTreeIsInDangerCondition condition\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the FStateTreeIsInDangerCondition condition" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character to check danger status on */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character to check danger status on" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinReactionTime_MetaData[] = {
		{ "Category", "Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum time to wait before reacting to the danger event */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum time to wait before reacting to the danger event" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxReactionTime_MetaData[] = {
		{ "Category", "Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum time to wait before ignoring the danger event */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum time to wait before ignoring the danger event" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DangerSightConeAngle_MetaData[] = {
		{ "Category", "Parameters" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Line of sight half angle for detecting incoming danger, in degrees*/" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Line of sight half angle for detecting incoming danger, in degrees" },
#endif
		{ "Units", "degrees" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeIsInDangerConditionInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MinReactionTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxReactionTime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DangerSightConeAngle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeIsInDangerConditionInstanceData constinit property declarations 
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeIsInDangerConditionInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeIsInDangerConditionInstanceData Property Definitions ****
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeIsInDangerConditionInstanceData, Character), Z_Construct_UClass_ACombatEnemy, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MinReactionTime = { "MinReactionTime", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeIsInDangerConditionInstanceData, MinReactionTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinReactionTime_MetaData), NewProp_MinReactionTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxReactionTime = { "MaxReactionTime", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeIsInDangerConditionInstanceData, MaxReactionTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxReactionTime_MetaData), NewProp_MaxReactionTime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DangerSightConeAngle = { "DangerSightConeAngle", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeIsInDangerConditionInstanceData, DangerSightConeAngle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DangerSightConeAngle_MetaData), NewProp_DangerSightConeAngle_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MinReactionTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxReactionTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DangerSightConeAngle,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeIsInDangerConditionInstanceData Property Definitions ******
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeIsInDangerConditionInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeIsInDangerConditionInstanceData>(),
	alignof(FStateTreeIsInDangerConditionInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeIsInDangerConditionInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeIsInDangerConditionInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeIsInDangerConditionInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeIsInDangerConditionInstanceData ***************************

// ********** Begin ScriptStruct FStateTreeIsInDangerCondition *************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeIsInDangerCondition_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeIsInDangerCondition>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeIsInDangerCondition); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree condition to check if the character is about to be hit by an attack\n */" },
#endif
		{ "DisplayName", "Character is in Danger" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree condition to check if the character is about to be hit by an attack" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeIsInDangerCondition constinit property declarations *****
// ********** End ScriptStruct FStateTreeIsInDangerCondition constinit property declarations *******
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeIsInDangerCondition>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeIsInDangerCondition>() == std::is_polymorphic<FStateTreeConditionCommonBase>(), "USTRUCT FStateTreeIsInDangerCondition cannot be polymorphic unless super FStateTreeConditionCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeConditionCommonBase,
	&NewStructOps,
	"StateTreeIsInDangerCondition",
	nullptr,
	0,
	DataSizeOf<FStateTreeIsInDangerCondition>(),
	alignof(FStateTreeIsInDangerCondition),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeIsInDangerCondition(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeIsInDangerCondition, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeIsInDangerCondition"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeIsInDangerCondition ***************************************

// ********** Begin ScriptStruct FStateTreeAttackInstanceData **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeAttackInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeAttackInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Combat StateTree tasks\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Combat StateTree tasks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that will perform the attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that will perform the attack" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeAttackInstanceData constinit property declarations ******
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeAttackInstanceData constinit property declarations ********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeAttackInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeAttackInstanceData Property Definitions *****************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeAttackInstanceData, Character), Z_Construct_UClass_ACombatEnemy, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeAttackInstanceData Property Definitions *******************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeAttackInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeAttackInstanceData>(),
	alignof(FStateTreeAttackInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeAttackInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeAttackInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeAttackInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeAttackInstanceData ****************************************

// ********** Begin ScriptStruct FStateTreeComboAttackTask *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeComboAttackTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeComboAttackTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to perform a combo attack\n */" },
#endif
		{ "DisplayName", "Combo Attack" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to perform a combo attack" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeComboAttackTask constinit property declarations *********
// ********** End ScriptStruct FStateTreeComboAttackTask constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeComboAttackTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeComboAttackTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeComboAttackTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeComboAttackTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeComboAttackTask>(),
	alignof(FStateTreeComboAttackTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeComboAttackTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeComboAttackTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeComboAttackTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeComboAttackTask *******************************************

// ********** Begin ScriptStruct FStateTreeChargedAttackTask ***************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeChargedAttackTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeChargedAttackTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to perform a charged attack\n */" },
#endif
		{ "DisplayName", "Charged Attack" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to perform a charged attack" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeChargedAttackTask constinit property declarations *******
// ********** End ScriptStruct FStateTreeChargedAttackTask constinit property declarations *********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeChargedAttackTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeChargedAttackTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeChargedAttackTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeChargedAttackTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeChargedAttackTask>(),
	alignof(FStateTreeChargedAttackTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeChargedAttackTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeChargedAttackTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeChargedAttackTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeChargedAttackTask *****************************************

// ********** Begin ScriptStruct FStateTreeWaitForLandingTask **************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeWaitForLandingTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeWaitForLandingTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to wait for the character to land\n */" },
#endif
		{ "DisplayName", "Wait for Landing" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to wait for the character to land" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeWaitForLandingTask constinit property declarations ******
// ********** End ScriptStruct FStateTreeWaitForLandingTask constinit property declarations ********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeWaitForLandingTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeWaitForLandingTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeWaitForLandingTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeWaitForLandingTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeWaitForLandingTask>(),
	alignof(FStateTreeWaitForLandingTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeWaitForLandingTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeWaitForLandingTask ****************************************

// ********** Begin ScriptStruct FStateTreeFaceActorInstanceData ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceActorInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceActorInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Face Towards Actor StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Face Towards Actor StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI Controller that will determine the focused actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Controller that will determine the focused actor" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorToFaceTowards_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Actor that will be faced towards */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Actor that will be faced towards" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceActorInstanceData constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorToFaceTowards;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeFaceActorInstanceData constinit property declarations *****
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceActorInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeFaceActorInstanceData Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceActorInstanceData, Controller), Z_Construct_UClass_AAIController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActorToFaceTowards = { "ActorToFaceTowards", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceActorInstanceData, ActorToFaceTowards), Z_Construct_UClass_AActor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorToFaceTowards_MetaData), NewProp_ActorToFaceTowards_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActorToFaceTowards,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeFaceActorInstanceData Property Definitions ****************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeFaceActorInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeFaceActorInstanceData>(),
	alignof(FStateTreeFaceActorInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeFaceActorInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceActorInstanceData *************************************

// ********** Begin ScriptStruct FStateTreeFaceActorTask *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceActorTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceActorTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to face an AI-Controlled Pawn towards an Actor\n */" },
#endif
		{ "DisplayName", "Face Towards Actor" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to face an AI-Controlled Pawn towards an Actor" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceActorTask constinit property declarations ***********
// ********** End ScriptStruct FStateTreeFaceActorTask constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceActorTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeFaceActorTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeFaceActorTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeFaceActorTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeFaceActorTask>(),
	alignof(FStateTreeFaceActorTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceActorTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceActorTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeFaceActorTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceActorTask *********************************************

// ********** Begin ScriptStruct FStateTreeFaceLocationInstanceData ********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceLocationInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceLocationInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Face Towards Location StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Face Towards Location StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AI Controller that will determine the focused location */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AI Controller that will determine the focused location" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FaceLocation_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Location that will be faced towards */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Location that will be faced towards" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceLocationInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FStructPropertyParams NewProp_FaceLocation;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeFaceLocationInstanceData constinit property declarations **
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceLocationInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeFaceLocationInstanceData Property Definitions ***********
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceLocationInstanceData, Controller), Z_Construct_UClass_AAIController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_FaceLocation = { "FaceLocation", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeFaceLocationInstanceData, FaceLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FaceLocation_MetaData), NewProp_FaceLocation_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FaceLocation,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeFaceLocationInstanceData Property Definitions *************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeFaceLocationInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeFaceLocationInstanceData>(),
	alignof(FStateTreeFaceLocationInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeFaceLocationInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceLocationInstanceData **********************************

// ********** Begin ScriptStruct FStateTreeFaceLocationTask ****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeFaceLocationTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeFaceLocationTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to face an AI-Controlled Pawn towards a world location\n */" },
#endif
		{ "DisplayName", "Face Towards Location" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to face an AI-Controlled Pawn towards a world location" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeFaceLocationTask constinit property declarations ********
// ********** End ScriptStruct FStateTreeFaceLocationTask constinit property declarations **********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeFaceLocationTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeFaceLocationTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeFaceLocationTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeFaceLocationTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeFaceLocationTask>(),
	alignof(FStateTreeFaceLocationTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeFaceLocationTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeFaceLocationTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeFaceLocationTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeFaceLocationTask ******************************************

// ********** Begin ScriptStruct FStateTreeSetCharacterSpeedInstanceData ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeSetCharacterSpeedInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeSetCharacterSpeedInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Set Character Speed StateTree task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Set Character Speed StateTree task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that will be affected */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that will be affected" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Speed_MetaData[] = {
		{ "Category", "Parameter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max ground speed to set for the character */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max ground speed to set for the character" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeSetCharacterSpeedInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Speed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeSetCharacterSpeedInstanceData constinit property declarations 
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSetCharacterSpeedInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeSetCharacterSpeedInstanceData Property Definitions ******
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSetCharacterSpeedInstanceData, Character), Z_Construct_UClass_ACharacter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeSetCharacterSpeedInstanceData, Speed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Speed_MetaData), NewProp_Speed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Speed,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeSetCharacterSpeedInstanceData Property Definitions ********
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeSetCharacterSpeedInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeSetCharacterSpeedInstanceData>(),
	alignof(FStateTreeSetCharacterSpeedInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeSetCharacterSpeedInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeSetCharacterSpeedInstanceData *****************************

// ********** Begin ScriptStruct FStateTreeSetCharacterSpeedTask ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeSetCharacterSpeedTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeSetCharacterSpeedTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to change a Character's ground speed\n */" },
#endif
		{ "DisplayName", "Set Character Speed" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to change a Character's ground speed" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeSetCharacterSpeedTask constinit property declarations ***
// ********** End ScriptStruct FStateTreeSetCharacterSpeedTask constinit property declarations *****
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeSetCharacterSpeedTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeSetCharacterSpeedTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeSetCharacterSpeedTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeSetCharacterSpeedTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeSetCharacterSpeedTask>(),
	alignof(FStateTreeSetCharacterSpeedTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeSetCharacterSpeedTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeSetCharacterSpeedTask *************************************

// ********** Begin ScriptStruct FStateTreeGetPlayerInfoInstanceData *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeGetPlayerInfoInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeGetPlayerInfoInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data struct for the Get Player Info task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data struct for the Get Player Info task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Character_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that owns this task */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that owns this task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayerCharacter_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character that owns this task */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character that owns this task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayerLocation_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Last known location for the target */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Last known location for the target" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DistanceToTarget_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance to the target */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance to the target" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxRange_MetaData[] = {
		{ "Category", "Parameter" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum allowed targeting range */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum allowed targeting range" },
#endif
		{ "Units", "cm" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeGetPlayerInfoInstanceData constinit property declarations 
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Character;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetPlayerCharacter;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TargetPlayerLocation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DistanceToTarget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxRange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeGetPlayerInfoInstanceData constinit property declarations *
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerInfoInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeGetPlayerInfoInstanceData Property Definitions **********
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Character = { "Character", nullptr, (EPropertyFlags)0x0114000000000001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, Character), Z_Construct_UClass_ACharacter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Character_MetaData), NewProp_Character_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TargetPlayerCharacter = { "TargetPlayerCharacter", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, TargetPlayerCharacter), Z_Construct_UClass_ACharacter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayerCharacter_MetaData), NewProp_TargetPlayerCharacter_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_TargetPlayerLocation = { "TargetPlayerLocation", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, TargetPlayerLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayerLocation_MetaData), NewProp_TargetPlayerLocation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DistanceToTarget = { "DistanceToTarget", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, DistanceToTarget), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DistanceToTarget_MetaData), NewProp_DistanceToTarget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxRange = { "MaxRange", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInfoInstanceData, MaxRange), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxRange_MetaData), NewProp_MaxRange_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Character,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetPlayerCharacter,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetPlayerLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DistanceToTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxRange,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeGetPlayerInfoInstanceData Property Definitions ************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeGetPlayerInfoInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeGetPlayerInfoInstanceData>(),
	alignof(FStateTreeGetPlayerInfoInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeGetPlayerInfoInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeGetPlayerInfoInstanceData *********************************

// ********** Begin ScriptStruct FStateTreeGetPlayerInfoTask ***************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeGetPlayerInfoTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeGetPlayerInfoTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to get information about the player character\n */" },
#endif
		{ "DisplayName", "GetPlayerInfo" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to get information about the player character" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeGetPlayerInfoTask constinit property declarations *******
// ********** End ScriptStruct FStateTreeGetPlayerInfoTask constinit property declarations *********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerInfoTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeGetPlayerInfoTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeGetPlayerInfoTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeGetPlayerInfoTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeGetPlayerInfoTask>(),
	alignof(FStateTreeGetPlayerInfoTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeGetPlayerInfoTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeGetPlayerInfoTask *****************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatStateTreeUtility_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData, Z_Construct_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData_Statics::NewStructOps, TEXT("StateTreeCharacterGroundedConditionInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedConditionInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeCharacterGroundedConditionInstanceData), 3732760818U) },
		{ Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition, Z_Construct_UScriptStruct_FStateTreeCharacterGroundedCondition_Statics::NewStructOps, TEXT("StateTreeCharacterGroundedCondition"),&Z_Registration_Info_UScriptStruct_FStateTreeCharacterGroundedCondition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeCharacterGroundedCondition), 3637652779U) },
		{ Z_Construct_UScriptStruct_FStateTreeIsInDangerConditionInstanceData, Z_Construct_UScriptStruct_FStateTreeIsInDangerConditionInstanceData_Statics::NewStructOps, TEXT("StateTreeIsInDangerConditionInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerConditionInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeIsInDangerConditionInstanceData), 285813001U) },
		{ Z_Construct_UScriptStruct_FStateTreeIsInDangerCondition, Z_Construct_UScriptStruct_FStateTreeIsInDangerCondition_Statics::NewStructOps, TEXT("StateTreeIsInDangerCondition"),&Z_Registration_Info_UScriptStruct_FStateTreeIsInDangerCondition, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeIsInDangerCondition), 4101081734U) },
		{ Z_Construct_UScriptStruct_FStateTreeAttackInstanceData, Z_Construct_UScriptStruct_FStateTreeAttackInstanceData_Statics::NewStructOps, TEXT("StateTreeAttackInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeAttackInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeAttackInstanceData), 3773657373U) },
		{ Z_Construct_UScriptStruct_FStateTreeComboAttackTask, Z_Construct_UScriptStruct_FStateTreeComboAttackTask_Statics::NewStructOps, TEXT("StateTreeComboAttackTask"),&Z_Registration_Info_UScriptStruct_FStateTreeComboAttackTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeComboAttackTask), 2159363523U) },
		{ Z_Construct_UScriptStruct_FStateTreeChargedAttackTask, Z_Construct_UScriptStruct_FStateTreeChargedAttackTask_Statics::NewStructOps, TEXT("StateTreeChargedAttackTask"),&Z_Registration_Info_UScriptStruct_FStateTreeChargedAttackTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeChargedAttackTask), 2819724529U) },
		{ Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask, Z_Construct_UScriptStruct_FStateTreeWaitForLandingTask_Statics::NewStructOps, TEXT("StateTreeWaitForLandingTask"),&Z_Registration_Info_UScriptStruct_FStateTreeWaitForLandingTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeWaitForLandingTask), 584154258U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData, Z_Construct_UScriptStruct_FStateTreeFaceActorInstanceData_Statics::NewStructOps, TEXT("StateTreeFaceActorInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceActorInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceActorInstanceData), 2679187444U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceActorTask, Z_Construct_UScriptStruct_FStateTreeFaceActorTask_Statics::NewStructOps, TEXT("StateTreeFaceActorTask"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceActorTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceActorTask), 2497602182U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData, Z_Construct_UScriptStruct_FStateTreeFaceLocationInstanceData_Statics::NewStructOps, TEXT("StateTreeFaceLocationInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceLocationInstanceData), 1489484892U) },
		{ Z_Construct_UScriptStruct_FStateTreeFaceLocationTask, Z_Construct_UScriptStruct_FStateTreeFaceLocationTask_Statics::NewStructOps, TEXT("StateTreeFaceLocationTask"),&Z_Registration_Info_UScriptStruct_FStateTreeFaceLocationTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeFaceLocationTask), 4139618016U) },
		{ Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData, Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData_Statics::NewStructOps, TEXT("StateTreeSetCharacterSpeedInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSetCharacterSpeedInstanceData), 3195879496U) },
		{ Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask, Z_Construct_UScriptStruct_FStateTreeSetCharacterSpeedTask_Statics::NewStructOps, TEXT("StateTreeSetCharacterSpeedTask"),&Z_Registration_Info_UScriptStruct_FStateTreeSetCharacterSpeedTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeSetCharacterSpeedTask), 3831772349U) },
		{ Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData, Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoInstanceData_Statics::NewStructOps, TEXT("StateTreeGetPlayerInfoInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerInfoInstanceData), 2636064915U) },
		{ Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask, Z_Construct_UScriptStruct_FStateTreeGetPlayerInfoTask_Statics::NewStructOps, TEXT("StateTreeGetPlayerInfoTask"),&Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInfoTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerInfoTask), 3188098726U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatStateTreeUtility_h__Script_DemoGame_b457f6dbfbf0bca5333aae8ae9e7793e964fd5f7{
	TEXT("/Script/DemoGame"),
	nullptr, 0,
	UHT_STATICS::ScriptStructInfo, UE_ARRAY_COUNT(UHT_STATICS::ScriptStructInfo),
	nullptr, 0,
	nullptr, 0,
};
#undef UHT_STATICS
// ********** End Registration *********************************************************************
#undef UHT_STRUCT_BASE

PRAGMA_ENABLE_DEPRECATION_WARNINGS
