// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
ENGINE_API UEnum* Z_Construct_UEnum_Engine_ECollisionChannel(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent(ETypeConstructPhase);
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingCharacter(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingCharacter(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingCharacter Function DoDrop **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingCharacter_DoDrop_Statics
struct UHT_STATICS
{
	struct SideScrollingCharacter_eventDoDrop_Parms
	{
		float Value;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles drop inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles drop inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoDrop constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoDrop constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoDrop Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingCharacter_eventDoDrop_Parms, Value), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoDrop Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingCharacter, nullptr, "DoDrop", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingCharacter_eventDoDrop_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingCharacter_eventDoDrop_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingCharacter_DoDrop(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingCharacter::execDoDrop)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Value);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoDrop(Z_Param_Value);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingCharacter Function DoDrop ************************************

// ********** Begin Class ASideScrollingCharacter Function DoInteract ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingCharacter_DoInteract_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles interact inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles interact inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoInteract constinit property declarations ****************************
// ********** End Function DoInteract constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingCharacter, nullptr, "DoInteract", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ASideScrollingCharacter_DoInteract(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingCharacter::execDoInteract)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoInteract();
	P_NATIVE_END;
}
// ********** End Class ASideScrollingCharacter Function DoInteract ********************************

// ********** Begin Class ASideScrollingCharacter Function DoJumpEnd *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingCharacter_DoJumpEnd_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpEnd constinit property declarations *****************************
// ********** End Function DoJumpEnd constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingCharacter, nullptr, "DoJumpEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ASideScrollingCharacter_DoJumpEnd(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingCharacter::execDoJumpEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpEnd();
	P_NATIVE_END;
}
// ********** End Class ASideScrollingCharacter Function DoJumpEnd *********************************

// ********** Begin Class ASideScrollingCharacter Function DoJumpStart *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingCharacter_DoJumpStart_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpStart constinit property declarations ***************************
// ********** End Function DoJumpStart constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingCharacter, nullptr, "DoJumpStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ASideScrollingCharacter_DoJumpStart(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingCharacter::execDoJumpStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpStart();
	P_NATIVE_END;
}
// ********** End Class ASideScrollingCharacter Function DoJumpStart *******************************

// ********** Begin Class ASideScrollingCharacter Function DoMove **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingCharacter_DoMove_Statics
struct UHT_STATICS
{
	struct SideScrollingCharacter_eventDoMove_Parms
	{
		float Forward;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles move inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles move inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoMove constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Forward;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoMove constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoMove Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Forward = { "Forward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingCharacter_eventDoMove_Parms, Forward), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Forward,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoMove Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingCharacter, nullptr, "DoMove", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingCharacter_eventDoMove_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingCharacter_eventDoMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingCharacter_DoMove(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingCharacter::execDoMove)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Forward);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoMove(Z_Param_Forward);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingCharacter Function DoMove ************************************

// ********** Begin Class ASideScrollingCharacter Function HasDoubleJumped *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingCharacter_HasDoubleJumped_Statics
struct UHT_STATICS
{
	struct SideScrollingCharacter_eventHasDoubleJumped_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Side Scrolling" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns true if the character has just double jumped */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the character has just double jumped" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HasDoubleJumped constinit property declarations ***********************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SideScrollingCharacter_eventHasDoubleJumped_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasDoubleJumped constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasDoubleJumped Property Definitions **********************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(SideScrollingCharacter_eventHasDoubleJumped_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HasDoubleJumped Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingCharacter, nullptr, "HasDoubleJumped", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingCharacter_eventHasDoubleJumped_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingCharacter_eventHasDoubleJumped_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingCharacter_HasDoubleJumped(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingCharacter::execHasDoubleJumped)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasDoubleJumped();
	P_NATIVE_END;
}
// ********** End Class ASideScrollingCharacter Function HasDoubleJumped ***************************

// ********** Begin Class ASideScrollingCharacter Function HasWallJumped ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingCharacter_HasWallJumped_Statics
struct UHT_STATICS
{
	struct SideScrollingCharacter_eventHasWallJumped_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Side Scrolling" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Returns true if the character has just wall jumped */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns true if the character has just wall jumped" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function HasWallJumped constinit property declarations *************************
	static void NewProp_ReturnValue_SetBit(void* Obj)
	{
		((SideScrollingCharacter_eventHasWallJumped_Parms*)Obj)->ReturnValue = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function HasWallJumped constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function HasWallJumped Property Definitions ************************************
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(SideScrollingCharacter_eventHasWallJumped_Parms), &UHT_STATICS::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function HasWallJumped Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingCharacter, nullptr, "HasWallJumped", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingCharacter_eventHasWallJumped_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingCharacter_eventHasWallJumped_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingCharacter_HasWallJumped(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingCharacter::execHasWallJumped)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=P_THIS->HasWallJumped();
	P_NATIVE_END;
}
// ********** End Class ASideScrollingCharacter Function HasWallJumped *****************************

// ********** Begin Class ASideScrollingCharacter **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A player-controllable character side scrolling game\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A player-controllable character side scrolling game" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Camera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Player camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Player camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DropAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Drop from Platform Action */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Drop from Platform Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Interact Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Interact Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpPushImpulse_MetaData[] = {
		{ "Category", "Side Scrolling|Jump" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Impulse to manually push physics objects while we're in midair */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Impulse to manually push physics objects while we're in midair" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InteractionRadius_MetaData[] = {
		{ "Category", "Side Scrolling|Interaction" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max distance that interactive objects can be triggered */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max distance that interactive objects can be triggered" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DelayBetweenWallJumps_MetaData[] = {
		{ "Category", "Side Scrolling|Wall Jump" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to disable input after a wall jump to preserve momentum */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to disable input after a wall jump to preserve momentum" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpTraceDistance_MetaData[] = {
		{ "Category", "Side Scrolling|Wall Jump" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance to trace ahead of the character for wall jumps */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance to trace ahead of the character for wall jumps" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpHorizontalImpulse_MetaData[] = {
		{ "Category", "Side Scrolling|Wall Jump" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Horizontal impulse to apply to the character during wall jumps */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Horizontal impulse to apply to the character during wall jumps" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallJumpVerticalMultiplier_MetaData[] = {
		{ "Category", "Side Scrolling|Wall Jump" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Multiplies the jump Z velocity for wall jumps. */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Multiplies the jump Z velocity for wall jumps." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoftCollisionObjectType_MetaData[] = {
		{ "Category", "Side Scrolling|Soft Platforms" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Collision object type to use for soft collision traces (dropping down floors) */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Collision object type to use for soft collision traces (dropping down floors)" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SoftCollisionTraceDistance_MetaData[] = {
		{ "Category", "Side Scrolling|Soft Platforms" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance to trace down during soft collision checks */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance to trace down during soft collision checks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxCoyoteTime_MetaData[] = {
		{ "Category", "Side Scrolling|Coyote Time" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of time that can pass since we started falling when we allow a regular jump */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of time that can pass since we started falling when we allow a regular jump" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingCharacter constinit property declarations ******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Camera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DropAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_InteractAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_JumpPushImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InteractionRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DelayBetweenWallJumps;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpHorizontalImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallJumpVerticalMultiplier;
	static const UECodeGen_Private::FBytePropertyParams NewProp_SoftCollisionObjectType;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SoftCollisionTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxCoyoteTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingCharacter constinit property declarations ********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DoDrop"), .Pointer = &ASideScrollingCharacter::execDoDrop },
		{ .NameUTF8 = UTF8TEXT("DoInteract"), .Pointer = &ASideScrollingCharacter::execDoInteract },
		{ .NameUTF8 = UTF8TEXT("DoJumpEnd"), .Pointer = &ASideScrollingCharacter::execDoJumpEnd },
		{ .NameUTF8 = UTF8TEXT("DoJumpStart"), .Pointer = &ASideScrollingCharacter::execDoJumpStart },
		{ .NameUTF8 = UTF8TEXT("DoMove"), .Pointer = &ASideScrollingCharacter::execDoMove },
		{ .NameUTF8 = UTF8TEXT("HasDoubleJumped"), .Pointer = &ASideScrollingCharacter::execHasDoubleJumped },
		{ .NameUTF8 = UTF8TEXT("HasWallJumped"), .Pointer = &ASideScrollingCharacter::execHasWallJumped },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingCharacter_DoDrop, "DoDrop" }, // b44678702ee47e6057fe4e4d47c263d2280d7636
		{ &Z_Construct_UFunction_ASideScrollingCharacter_DoInteract, "DoInteract" }, // 42f5bf46d03e460a60d7fb32bbfa8348d2bcdd73
		{ &Z_Construct_UFunction_ASideScrollingCharacter_DoJumpEnd, "DoJumpEnd" }, // f0ac30e7d2d82f614029e652f7a0b4dabd0e7fbb
		{ &Z_Construct_UFunction_ASideScrollingCharacter_DoJumpStart, "DoJumpStart" }, // 66452ba88dbe3cadcd92551a938ee279dde59963
		{ &Z_Construct_UFunction_ASideScrollingCharacter_DoMove, "DoMove" }, // 3fbf744bf81f79960966816e3de5ca126655625b
		{ &Z_Construct_UFunction_ASideScrollingCharacter_HasDoubleJumped, "HasDoubleJumped" }, // cac0c7bf5f7d7f771b77e7d55523aa5acd4041ae
		{ &Z_Construct_UFunction_ASideScrollingCharacter_HasWallJumped, "HasWallJumped" }, // 36e924892431f7bdf12cda30ac76ec68a89a6ae8
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingCharacter Property Definitions *****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Camera = { "Camera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, Camera), Z_Construct_UClass_UCameraComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Camera_MetaData), NewProp_Camera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, MoveAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, JumpAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DropAction = { "DropAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, DropAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DropAction_MetaData), NewProp_DropAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_InteractAction = { "InteractAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, InteractAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractAction_MetaData), NewProp_InteractAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_JumpPushImpulse = { "JumpPushImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, JumpPushImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpPushImpulse_MetaData), NewProp_JumpPushImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InteractionRadius = { "InteractionRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, InteractionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InteractionRadius_MetaData), NewProp_InteractionRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DelayBetweenWallJumps = { "DelayBetweenWallJumps", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, DelayBetweenWallJumps), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DelayBetweenWallJumps_MetaData), NewProp_DelayBetweenWallJumps_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WallJumpTraceDistance = { "WallJumpTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, WallJumpTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpTraceDistance_MetaData), NewProp_WallJumpTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WallJumpHorizontalImpulse = { "WallJumpHorizontalImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, WallJumpHorizontalImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpHorizontalImpulse_MetaData), NewProp_WallJumpHorizontalImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_WallJumpVerticalMultiplier = { "WallJumpVerticalMultiplier", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, WallJumpVerticalMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallJumpVerticalMultiplier_MetaData), NewProp_WallJumpVerticalMultiplier_MetaData) };
const UECodeGen_Private::FBytePropertyParams UHT_STATICS::NewProp_SoftCollisionObjectType = { "SoftCollisionObjectType", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Byte, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, SoftCollisionObjectType), Z_Construct_UEnum_Engine_ECollisionChannel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoftCollisionObjectType_MetaData), NewProp_SoftCollisionObjectType_MetaData) }; // 3aff698625c18cc2ccaa87a587b2eac8c50cdec7
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_SoftCollisionTraceDistance = { "SoftCollisionTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, SoftCollisionTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SoftCollisionTraceDistance_MetaData), NewProp_SoftCollisionTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxCoyoteTime = { "MaxCoyoteTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCharacter, MaxCoyoteTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxCoyoteTime_MetaData), NewProp_MaxCoyoteTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Camera,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DropAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InteractAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JumpPushImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InteractionRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DelayBetweenWallJumps,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WallJumpTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WallJumpHorizontalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_WallJumpVerticalMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoftCollisionObjectType,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SoftCollisionTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxCoyoteTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingCharacter Property Definitions *******************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ACharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingCharacter,
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
static void ASideScrollingCharacter_StaticRegisterNativesASideScrollingCharacter()
{
	UClass* Class = ASideScrollingCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingCharacter;
UClass* Z_Construct_UClass_ASideScrollingCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingCharacter;
		if (!Z_Registration_Info_UClass_ASideScrollingCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingCharacter"),
				Z_Registration_Info_UClass_ASideScrollingCharacter.InnerSingleton,
				ASideScrollingCharacter_StaticRegisterNativesASideScrollingCharacter,
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
		return Z_Registration_Info_UClass_ASideScrollingCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingCharacter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingCharacter);
ASideScrollingCharacter::~ASideScrollingCharacter() {}
// ********** End Class ASideScrollingCharacter ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingCharacter_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingCharacter, TEXT("ASideScrollingCharacter"), &Z_Registration_Info_UClass_ASideScrollingCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingCharacter), 405220295U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingCharacter_h__Script_DemoGame_07cb5afe5521470954069776a882418e8584d7e0{
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
