// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "PlatformingCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodePlatformingCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent(ETypeConstructPhase);
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_APlatformingCharacter(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_APlatformingCharacter(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class APlatformingCharacter Function DoDash ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_DoDash_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles dash inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles dash inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoDash constinit property declarations ********************************
// ********** End Function DoDash constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "DoDash", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoDash(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(APlatformingCharacter::execDoDash)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoDash();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoDash **************************************

// ********** Begin Class APlatformingCharacter Function DoJumpEnd *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpEnd constinit property declarations *****************************
// ********** End Function DoJumpEnd constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "DoJumpEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(APlatformingCharacter::execDoJumpEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpEnd();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoJumpEnd ***********************************

// ********** Begin Class APlatformingCharacter Function DoJumpStart *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_DoJumpStart_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpStart constinit property declarations ***************************
// ********** End Function DoJumpStart constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "DoJumpStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoJumpStart(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(APlatformingCharacter::execDoJumpStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpStart();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoJumpStart *********************************

// ********** Begin Class APlatformingCharacter Function DoLook ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_DoLook_Statics
struct UHT_STATICS
{
	struct PlatformingCharacter_eventDoLook_Parms
	{
		float Yaw;
		float Pitch;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles look inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles look inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoLook constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Yaw;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Pitch;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoLook constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoLook Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Yaw = { "Yaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoLook_Parms, Yaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Pitch = { "Pitch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoLook_Parms, Pitch), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Yaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pitch,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoLook Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "DoLook", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::PlatformingCharacter_eventDoLook_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::PlatformingCharacter_eventDoLook_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoLook(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(APlatformingCharacter::execDoLook)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Yaw);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Pitch);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoLook(Z_Param_Yaw,Z_Param_Pitch);
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoLook **************************************

// ********** Begin Class APlatformingCharacter Function DoMove ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_DoMove_Statics
struct UHT_STATICS
{
	struct PlatformingCharacter_eventDoMove_Parms
	{
		float Right;
		float Forward;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles move inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles move inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoMove constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Right;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Forward;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoMove constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoMove Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoMove_Parms, Right), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Forward = { "Forward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(PlatformingCharacter_eventDoMove_Parms, Forward), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Right,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Forward,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoMove Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "DoMove", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::PlatformingCharacter_eventDoMove_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::PlatformingCharacter_eventDoMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_DoMove(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(APlatformingCharacter::execDoMove)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Right);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Forward);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoMove(Z_Param_Right,Z_Param_Forward);
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function DoMove **************************************

// ********** Begin Class APlatformingCharacter Function HasDoubleJumped ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped_Statics
struct UHT_STATICS
{
	struct PlatformingCharacter_eventHasDoubleJumped_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Platforming" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns true if the character has just double jumped */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the character has just double jumped" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HasDoubleJumped constinit property declarations ***********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((PlatformingCharacter_eventHasDoubleJumped_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasDoubleJumped constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasDoubleJumped Property Definitions **********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(PlatformingCharacter_eventHasDoubleJumped_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HasDoubleJumped Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "HasDoubleJumped", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::PlatformingCharacter_eventHasDoubleJumped_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::PlatformingCharacter_eventHasDoubleJumped_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(APlatformingCharacter::execHasDoubleJumped)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasDoubleJumped();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function HasDoubleJumped *****************************

// ********** Begin Class APlatformingCharacter Function HasWallJumped *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_HasWallJumped_Statics
struct UHT_STATICS
{
	struct PlatformingCharacter_eventHasWallJumped_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Platforming" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns true if the character has just wall jumped */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the character has just wall jumped" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HasWallJumped constinit property declarations *************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((PlatformingCharacter_eventHasWallJumped_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasWallJumped constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasWallJumped Property Definitions ************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(PlatformingCharacter_eventHasWallJumped_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HasWallJumped Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "HasWallJumped", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::PlatformingCharacter_eventHasWallJumped_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::PlatformingCharacter_eventHasWallJumped_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_HasWallJumped(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(APlatformingCharacter::execHasWallJumped)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasWallJumped();
	P_NATIVE_END;
}
// ********** End Class APlatformingCharacter Function HasWallJumped *******************************

// ********** Begin Class APlatformingCharacter Function SetJumpTrailState *************************
struct PlatformingCharacter_eventSetJumpTrailState_Parms
{
	bool bEnabled;
};
static FName NAME_APlatformingCharacter_SetJumpTrailState = FName(TEXT("SetJumpTrailState"));
void APlatformingCharacter::SetJumpTrailState(bool bEnabled)
{
	PlatformingCharacter_eventSetJumpTrailState_Parms Parms;
	Parms.bEnabled=bEnabled ? true : false;
	UFunction* Func = FindFunctionChecked(NAME_APlatformingCharacter_SetJumpTrailState);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Platforming" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Passes control to Blueprint to enable or disable jump trails */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Passes control to Blueprint to enable or disable jump trails" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetJumpTrailState constinit property declarations *********************
	static void NewProp_bEnabled_SetBit(void* Obj)
	{
		((PlatformingCharacter_eventSetJumpTrailState_Parms*)Obj)->bEnabled = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnabled;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetJumpTrailState constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetJumpTrailState Property Definitions ********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bEnabled = { "bEnabled", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(PlatformingCharacter_eventSetJumpTrailState_Parms), &UHT_STATICS::NewProp_bEnabled_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bEnabled,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetJumpTrailState Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_APlatformingCharacter, nullptr, "SetJumpTrailState", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<PlatformingCharacter_eventSetJumpTrailState_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(PlatformingCharacter_eventSetJumpTrailState_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class APlatformingCharacter Function SetJumpTrailState ***************************

// ********** Begin Class APlatformingCharacter ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_APlatformingCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  An enhanced Third Person Character with the following functionality:\n *  - Platforming game character movement physics\n *  - Press and Hold Jump\n *  - Double Jump\n *  - Wall Jump\n *  - Dash\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Platforming/PlatformingCharacter.h" },
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An enhanced Third Person Character with the following functionality:\n- Platforming game character movement physics\n- Press and Hold Jump\n- Double Jump\n- Wall Jump\n- Dash" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Follow camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseLookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mouse Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mouse Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DashAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Dash Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Dash Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpTraceDistance_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance to trace ahead of the character to look for walls to jump from */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance to trace ahead of the character to look for walls to jump from" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpTraceRadius_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the wall jump sphere trace check */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the wall jump sphere trace check" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpBounceImpulse_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Impulse to apply away from the wall when wall jumping */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Impulse to apply away from the wall when wall jumping" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpVerticalImpulse_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Vertical impulse to apply when wall jumping */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Vertical impulse to apply when wall jumping" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DelayBetweenWallJumps_MetaData[] = {
		{ "Category", "Wall Jump" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to ignore jump inputs after a wall jump */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to ignore jump inputs after a wall jump" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DashMontage_MetaData[] = {
		{ "Category", "Dash" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AnimMontage to use for the Dash action */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage to use for the Dash action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxCoyoteTime_MetaData[] = {
		{ "Category", "Coyote Time" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of time that can pass since we started falling when we allow a regular jump */" },
#endif
		{ "ModuleRelativePath", "Variant_Platforming/PlatformingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of time that can pass since we started falling when we allow a regular jump" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA

// ********** Begin Class APlatformingCharacter constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MouseLookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DashAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpTraceRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpBounceImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpVerticalImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DelayBetweenWallJumps;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DashMontage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxCoyoteTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class APlatformingCharacter constinit property declarations **********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DoDash"), .Pointer = &APlatformingCharacter::execDoDash },
		{ .NameUTF8 = UTF8TEXT("DoJumpEnd"), .Pointer = &APlatformingCharacter::execDoJumpEnd },
		{ .NameUTF8 = UTF8TEXT("DoJumpStart"), .Pointer = &APlatformingCharacter::execDoJumpStart },
		{ .NameUTF8 = UTF8TEXT("DoLook"), .Pointer = &APlatformingCharacter::execDoLook },
		{ .NameUTF8 = UTF8TEXT("DoMove"), .Pointer = &APlatformingCharacter::execDoMove },
		{ .NameUTF8 = UTF8TEXT("HasDoubleJumped"), .Pointer = &APlatformingCharacter::execHasDoubleJumped },
		{ .NameUTF8 = UTF8TEXT("HasWallJumped"), .Pointer = &APlatformingCharacter::execHasWallJumped },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_APlatformingCharacter_DoDash, "DoDash" }, // 3e7e8437f59fbc70ec51dadb48b5dfad8f1d0785
		{ &Z_Construct_UFunction_APlatformingCharacter_DoJumpEnd, "DoJumpEnd" }, // 5730ea50a1f159cef61f9df0a2aab27d8e1565d3
		{ &Z_Construct_UFunction_APlatformingCharacter_DoJumpStart, "DoJumpStart" }, // f4d73c66b5bf1c360a1f715e7d49cac5fdb95cb7
		{ &Z_Construct_UFunction_APlatformingCharacter_DoLook, "DoLook" }, // 735e1a09c8891caaecdc35a2f850de2846aba896
		{ &Z_Construct_UFunction_APlatformingCharacter_DoMove, "DoMove" }, // c656c0ea6fce3ee1a0aaec1d63332daddecd9214
		{ &Z_Construct_UFunction_APlatformingCharacter_HasDoubleJumped, "HasDoubleJumped" }, // 8372b3e1b1b418f52f5f914ed663a201678053a8
		{ &Z_Construct_UFunction_APlatformingCharacter_HasWallJumped, "HasWallJumped" }, // 9aed34f0db23dd0bae9b90c465da290f0bfb5edf
		{ &Z_Construct_UFunction_APlatformingCharacter_SetJumpTrailState, "SetJumpTrailState" }, // f0f9812a60e9254709d3d8c6ca2554d5cac5fe4c
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<APlatformingCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class APlatformingCharacter Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, JumpAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, MoveAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, LookAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MouseLookAction = { "MouseLookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, MouseLookAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseLookAction_MetaData), NewProp_MouseLookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DashAction = { "DashAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, DashAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DashAction_MetaData), NewProp_DashAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WallJumpTraceDistance = { "WallJumpTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpTraceDistance_MetaData), NewProp_WallJumpTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WallJumpTraceRadius = { "WallJumpTraceRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpTraceRadius_MetaData), NewProp_WallJumpTraceRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WallJumpBounceImpulse = { "WallJumpBounceImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpBounceImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpBounceImpulse_MetaData), NewProp_WallJumpBounceImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WallJumpVerticalImpulse = { "WallJumpVerticalImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, WallJumpVerticalImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpVerticalImpulse_MetaData), NewProp_WallJumpVerticalImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DelayBetweenWallJumps = { "DelayBetweenWallJumps", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, DelayBetweenWallJumps), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DelayBetweenWallJumps_MetaData), NewProp_DelayBetweenWallJumps_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DashMontage = { "DashMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, DashMontage), Z_Construct_UClass_UAnimMontage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DashMontage_MetaData), NewProp_DashMontage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxCoyoteTime = { "MaxCoyoteTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(APlatformingCharacter, MaxCoyoteTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxCoyoteTime_MetaData), NewProp_MaxCoyoteTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MouseLookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DashAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WallJumpTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WallJumpTraceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WallJumpBounceImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WallJumpVerticalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DelayBetweenWallJumps,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DashMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxCoyoteTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class APlatformingCharacter Property Definitions *********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ACharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_APlatformingCharacter,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x008000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void APlatformingCharacter_StaticRegisterNativesAPlatformingCharacter()
{
	UClass* Class = APlatformingCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_APlatformingCharacter;
UClass* Z_Construct_UClass_APlatformingCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = APlatformingCharacter;
		if (!Z_Registration_Info_UClass_APlatformingCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("PlatformingCharacter"),
				Z_Registration_Info_UClass_APlatformingCharacter.InnerSingleton,
				APlatformingCharacter_StaticRegisterNativesAPlatformingCharacter,
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
		return Z_Registration_Info_UClass_APlatformingCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_APlatformingCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_APlatformingCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_APlatformingCharacter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, APlatformingCharacter);
APlatformingCharacter::~APlatformingCharacter() {}
// ********** End Class APlatformingCharacter ******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Platforming_PlatformingCharacter_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_APlatformingCharacter, TEXT("APlatformingCharacter"), &Z_Registration_Info_UClass_APlatformingCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(APlatformingCharacter), 3748080242U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Platforming_PlatformingCharacter_h__Script_DemoGame_97436413a14a7531322e8801423031ccbfba3bef{
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
