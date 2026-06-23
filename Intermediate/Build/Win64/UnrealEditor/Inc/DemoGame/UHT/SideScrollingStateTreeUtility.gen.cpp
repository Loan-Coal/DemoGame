// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingStateTreeUtility.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingStateTreeUtility() {}

// ********** Begin Cross Module References ********************************************************
STATETREEMODULE_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeTaskCommonBase(ETypeConstructPhase);
AIMODULE_API UClass* Z_Construct_UClass_AAIController(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_APawn(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData(ETypeConstructPhase);
DEMOGAME_API UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerTask(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin ScriptStruct FStateTreeGetPlayerInstanceData ***********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeGetPlayerInstanceData>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeGetPlayerInstanceData); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Instance data for the FStateTreeGetPlayerTask task\n */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Instance data for the FStateTreeGetPlayerTask task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NPC_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** NPC owning this task */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "NPC owning this task" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Controller_MetaData[] = {
		{ "Category", "Context" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Holds the found player pawn */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Holds the found player pawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPlayer_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Holds the found player pawn */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Holds the found player pawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bValidTarget_MetaData[] = {
		{ "Category", "Output" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Is the pawn close enough to be considered a valid target? */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Is the pawn close enough to be considered a valid target?" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RangeMax_MetaData[] = {
		{ "Category", "Parameter" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max distance to be considered a valid target */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max distance to be considered a valid target" },
#endif
		{ "Units", "cm" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeGetPlayerInstanceData constinit property declarations ***
	static const UECodeGen_Private::FObjectPropertyParams NewProp_NPC;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Controller;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TargetPlayer;
	static void NewProp_bValidTarget_SetBit(void* Obj)
	{
		((FStateTreeGetPlayerInstanceData*)Obj)->bValidTarget = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bValidTarget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RangeMax;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FStateTreeGetPlayerInstanceData constinit property declarations *****
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerInstanceData>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS

// ********** Begin ScriptStruct FStateTreeGetPlayerInstanceData Property Definitions **************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_NPC = { "NPC", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, NPC), Z_Construct_UClass_APawn, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NPC_MetaData), NewProp_NPC_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Controller = { "Controller", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, Controller), Z_Construct_UClass_AAIController, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Controller_MetaData), NewProp_Controller_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_TargetPlayer = { "TargetPlayer", nullptr, (EPropertyFlags)0x0114000000020001, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, TargetPlayer), Z_Construct_UClass_APawn, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPlayer_MetaData), NewProp_TargetPlayer_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bValidTarget = { "bValidTarget", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(FStateTreeGetPlayerInstanceData), &UHT_STATICS::NewProp_bValidTarget_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bValidTarget_MetaData), NewProp_bValidTarget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RangeMax = { "RangeMax", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(FStateTreeGetPlayerInstanceData, RangeMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RangeMax_MetaData), NewProp_RangeMax_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NPC,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Controller,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_TargetPlayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bValidTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RangeMax,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End ScriptStruct FStateTreeGetPlayerInstanceData Property Definitions ****************
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	nullptr,
	&NewStructOps,
	"StateTreeGetPlayerInstanceData",
	UHT_STATICS::PropPointers,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	DataSizeOf<FStateTreeGetPlayerInstanceData>(),
	alignof(FStateTreeGetPlayerInstanceData),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeGetPlayerInstanceData"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeGetPlayerInstanceData *************************************

// ********** Begin ScriptStruct FStateTreeGetPlayerTask *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics
struct UHT_STATICS
{
	static inline consteval int32 GetStructSize() { return DataSizeOf<FStateTreeGetPlayerTask>(); }
	static inline consteval int16 GetStructAlignment() { return alignof(FStateTreeGetPlayerTask); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Side Scrolling" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  StateTree task to get the player-controlled character\n */" },
#endif
		{ "DisplayName", "Get Player" },
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingStateTreeUtility.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree task to get the player-controlled character" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FStateTreeGetPlayerTask constinit property declarations ***********
// ********** End ScriptStruct FStateTreeGetPlayerTask constinit property declarations *************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FStateTreeGetPlayerTask>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct UHT_STATICS
static_assert(std::is_polymorphic<FStateTreeGetPlayerTask>() == std::is_polymorphic<FStateTreeTaskCommonBase>(), "USTRUCT FStateTreeGetPlayerTask cannot be polymorphic unless super FStateTreeTaskCommonBase is polymorphic");
const UECodeGen_Private::FStructParams UHT_STATICS::StructParams = {
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
	Z_Construct_UScriptStruct_FStateTreeTaskCommonBase,
	&NewStructOps,
	"StateTreeGetPlayerTask",
	nullptr,
	0,
	DataSizeOf<FStateTreeGetPlayerTask>(),
	alignof(FStateTreeGetPlayerTask),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask;
UScriptStruct* Z_Construct_UScriptStruct_FStateTreeGetPlayerTask(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Outer)
	{
		if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton)
		{
			Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FStateTreeGetPlayerTask, (UObject*)Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase::Outer), TEXT("StateTreeGetPlayerTask"));
		}
		return Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.OuterSingleton;
	}
	if (!Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton, UHT_STATICS::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask.InnerSingleton);
}
#undef UHT_STATICS
// ********** End ScriptStruct FStateTreeGetPlayerTask *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_AI_SideScrollingStateTreeUtility_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData, Z_Construct_UScriptStruct_FStateTreeGetPlayerInstanceData_Statics::NewStructOps, TEXT("StateTreeGetPlayerInstanceData"),&Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerInstanceData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerInstanceData), 1033872423U) },
		{ Z_Construct_UScriptStruct_FStateTreeGetPlayerTask, Z_Construct_UScriptStruct_FStateTreeGetPlayerTask_Statics::NewStructOps, TEXT("StateTreeGetPlayerTask"),&Z_Registration_Info_UScriptStruct_FStateTreeGetPlayerTask, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FStateTreeGetPlayerTask), 4203551831U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_AI_SideScrollingStateTreeUtility_h__Script_DemoGame_0c215d6b2abd4d2828ef6e0ffdb90b8614efd528{
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
