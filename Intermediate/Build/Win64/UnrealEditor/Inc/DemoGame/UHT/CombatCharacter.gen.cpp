// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatCharacter() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor(ETypeConstructPhase);
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UAnimMontage(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent(ETypeConstructPhase);
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UWidgetComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatCharacter(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatAttacker(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatCharacter(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatDamageable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatLifeBar(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ACombatCharacter Function BP_ToggleCamera ********************************
static FName NAME_ACombatCharacter_BP_ToggleCamera = FName(TEXT("BP_ToggleCamera"));
void ACombatCharacter::BP_ToggleCamera()
{
	UFunction* Func = FindFunctionChecked(NAME_ACombatCharacter_BP_ToggleCamera);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_BP_ToggleCamera_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** BP hook to animate the camera side switch */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "BP hook to animate the camera side switch" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_ToggleCamera constinit property declarations ***********************
// ********** End Function BP_ToggleCamera constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "BP_ToggleCamera", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_BP_ToggleCamera(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ACombatCharacter Function BP_ToggleCamera **********************************

// ********** Begin Class ACombatCharacter Function DealtDamage ************************************
struct CombatCharacter_eventDealtDamage_Parms
{
	float Damage;
	FVector ImpactPoint;
};
static FName NAME_ACombatCharacter_DealtDamage = FName(TEXT("DealtDamage"));
void ACombatCharacter::DealtDamage(float Damage, FVector const& ImpactPoint)
{
	CombatCharacter_eventDealtDamage_Parms Parms;
	Parms.Damage=Damage;
	Parms.ImpactPoint=ImpactPoint;
	UFunction* Func = FindFunctionChecked(NAME_ACombatCharacter_DealtDamage);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_DealtDamage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to play damage dealt effects */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handler to play damage dealt effects" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImpactPoint_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function DealtDamage constinit property declarations ***************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Damage;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ImpactPoint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DealtDamage constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DealtDamage Property Definitions **************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDealtDamage_Parms, Damage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ImpactPoint = { "ImpactPoint", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDealtDamage_Parms, ImpactPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactPoint_MetaData), NewProp_ImpactPoint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Damage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactPoint,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DealtDamage Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "DealtDamage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<CombatCharacter_eventDealtDamage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(CombatCharacter_eventDealtDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_DealtDamage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ACombatCharacter Function DealtDamage **************************************

// ********** Begin Class ACombatCharacter Function DoChargedAttackEnd *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles charged attack released from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles charged attack released from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoChargedAttackEnd constinit property declarations ********************
// ********** End Function DoChargedAttackEnd constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "DoChargedAttackEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatCharacter::execDoChargedAttackEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoChargedAttackEnd();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoChargedAttackEnd *******************************

// ********** Begin Class ACombatCharacter Function DoChargedAttackStart ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles charged attack pressed from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles charged attack pressed from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoChargedAttackStart constinit property declarations ******************
// ********** End Function DoChargedAttackStart constinit property declarations ********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "DoChargedAttackStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatCharacter::execDoChargedAttackStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoChargedAttackStart();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoChargedAttackStart *****************************

// ********** Begin Class ACombatCharacter Function DoComboAttackEnd *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles combo attack released from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles combo attack released from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoComboAttackEnd constinit property declarations **********************
// ********** End Function DoComboAttackEnd constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "DoComboAttackEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatCharacter::execDoComboAttackEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoComboAttackEnd();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoComboAttackEnd *********************************

// ********** Begin Class ACombatCharacter Function DoComboAttackStart *****************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles combo attack pressed from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles combo attack pressed from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoComboAttackStart constinit property declarations ********************
// ********** End Function DoComboAttackStart constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "DoComboAttackStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatCharacter::execDoComboAttackStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoComboAttackStart();
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoComboAttackStart *******************************

// ********** Begin Class ACombatCharacter Function DoLook *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_DoLook_Statics
struct UHT_STATICS
{
	struct CombatCharacter_eventDoLook_Parms
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Yaw = { "Yaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoLook_Parms, Yaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Pitch = { "Pitch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoLook_Parms, Pitch), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Yaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pitch,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoLook Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "DoLook", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatCharacter_eventDoLook_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatCharacter_eventDoLook_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_DoLook(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatCharacter::execDoLook)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Yaw);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Pitch);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoLook(Z_Param_Yaw,Z_Param_Pitch);
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoLook *******************************************

// ********** Begin Class ACombatCharacter Function DoMove *****************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_DoMove_Statics
struct UHT_STATICS
{
	struct CombatCharacter_eventDoMove_Parms
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoMove_Parms, Right), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Forward = { "Forward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventDoMove_Parms, Forward), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Right,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Forward,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoMove Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "DoMove", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatCharacter_eventDoMove_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatCharacter_eventDoMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_DoMove(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatCharacter::execDoMove)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Right);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Forward);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoMove(Z_Param_Right,Z_Param_Forward);
	P_NATIVE_END;
}
// ********** End Class ACombatCharacter Function DoMove *******************************************

// ********** Begin Class ACombatCharacter Function ReceivedDamage *********************************
struct CombatCharacter_eventReceivedDamage_Parms
{
	float Damage;
	FVector ImpactPoint;
	FVector DamageDirection;
};
static FName NAME_ACombatCharacter_ReceivedDamage = FName(TEXT("ReceivedDamage"));
void ACombatCharacter::ReceivedDamage(float Damage, FVector const& ImpactPoint, FVector const& DamageDirection)
{
	CombatCharacter_eventReceivedDamage_Parms Parms;
	Parms.Damage=Damage;
	Parms.ImpactPoint=ImpactPoint;
	Parms.DamageDirection=DamageDirection;
	UFunction* Func = FindFunctionChecked(NAME_ACombatCharacter_ReceivedDamage);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatCharacter_ReceivedDamage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handler to play damage received effects */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Damage = { "Damage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventReceivedDamage_Parms, Damage), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_ImpactPoint = { "ImpactPoint", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventReceivedDamage_Parms, ImpactPoint), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImpactPoint_MetaData), NewProp_ImpactPoint_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_DamageDirection = { "DamageDirection", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatCharacter_eventReceivedDamage_Parms, DamageDirection), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageDirection_MetaData), NewProp_DamageDirection_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Damage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ImpactPoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DamageDirection,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ReceivedDamage Property Definitions *************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatCharacter, nullptr, "ReceivedDamage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<CombatCharacter_eventReceivedDamage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(CombatCharacter_eventReceivedDamage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatCharacter_ReceivedDamage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ACombatCharacter Function ReceivedDamage ***********************************

// ********** Begin Class ACombatCharacter *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ACombatCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  An enhanced Third Person Character with melee combat capabilities:\n *  - Combo attack string\n *  - Press and hold charged attack\n *  - Damage dealing and reaction\n *  - Death\n *  - Respawning\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_Combat/CombatCharacter.h" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "An enhanced Third Person Character with melee combat capabilities:\n- Combo attack string\n- Press and hold charged attack\n- Damage dealing and reaction\n- Death\n- Respawning" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifeBar_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Life bar widget component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Life bar widget component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseLookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mouse Look Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mouse Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboAttackAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Combo Attack Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Combo Attack Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargedAttackAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Charged Attack Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Charged Attack Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ToggleCameraAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Toggle Camera Side Input Action */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Toggle Camera Side Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxHP_MetaData[] = {
		{ "Category", "Damage" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of HP the character will have on respawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of HP the character will have on respawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Current amount of HP the character has */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Current amount of HP the character has" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifeBarColor_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Life bar widget fill color */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Life bar widget fill color" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PelvisBoneName_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the pelvis bone, for damage ragdoll physics */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pointer to the life bar widget" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackInputCacheTimeTolerance_MetaData[] = {
		{ "Category", "Melee Attack" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of time that may elapse for a non-combo attack input to not be considered stale */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of time that may elapse for a non-combo attack input to not be considered stale" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeTraceDistance_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "500" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance ahead of the character that melee attack sphere collision traces will extend */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance ahead of the character that melee attack sphere collision traces will extend" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeleeTraceRadius_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "200" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the sphere trace for melee attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the sphere trace for melee attacks" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DangerTraceDistance_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "500" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Distance ahead of the character that enemies will be notified of incoming attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Distance ahead of the character that enemies will be notified of incoming attacks" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DangerTraceRadius_MetaData[] = {
		{ "Category", "Melee Attack|Trace" },
		{ "ClampMax", "200" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Radius of the sphere trace to notify enemies of incoming attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Radius of the sphere trace to notify enemies of incoming attacks" },
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
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
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage that will play for combo attacks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboSectionNames_MetaData[] = {
		{ "Category", "Melee Attack|Combo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Names of the AnimMontage sections that correspond to each stage of the combo attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Names of the AnimMontage sections that correspond to each stage of the combo attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ComboInputCacheTimeTolerance_MetaData[] = {
		{ "Category", "Melee Attack|Combo" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Max amount of time that may elapse for a combo attack input to not be considered stale */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Max amount of time that may elapse for a combo attack input to not be considered stale" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargedAttackMontage_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** AnimMontage that will play for charged attacks */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimMontage that will play for charged attacks" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargeLoopSection_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the AnimMontage section that corresponds to the charge loop */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the AnimMontage section that corresponds to the charge loop" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ChargeAttackSection_MetaData[] = {
		{ "Category", "Melee Attack|Charged" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Name of the AnimMontage section that corresponds to the attack */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Name of the AnimMontage section that corresponds to the attack" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathCameraDistance_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom length while the character is dead */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom length while the character is dead" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultCameraDistance_MetaData[] = {
		{ "Category", "Camera" },
		{ "ClampMax", "1000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom length when the character respawns */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom length when the character respawns" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RespawnTime_MetaData[] = {
		{ "Category", "Respawn" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before respawning the character */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/CombatCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before respawning the character" },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA

// ********** Begin Class ACombatCharacter constinit property declarations *************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LifeBar;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MouseLookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ComboAttackAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChargedAttackAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ToggleCameraAction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxHP;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FStructPropertyParams NewProp_LifeBarColor;
	static const UECodeGen_Private::FNamePropertyParams NewProp_PelvisBoneName;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LifeBarWidget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackInputCacheTimeTolerance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeTraceRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DangerTraceDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DangerTraceRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeDamage;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeKnockbackImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MeleeLaunchImpulse;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ComboAttackMontage;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ComboSectionNames_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ComboSectionNames;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ComboInputCacheTimeTolerance;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ChargedAttackMontage;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ChargeLoopSection;
	static const UECodeGen_Private::FNamePropertyParams NewProp_ChargeAttackSection;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathCameraDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DefaultCameraDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RespawnTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ACombatCharacter constinit property declarations ***************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DoChargedAttackEnd"), .Pointer = &ACombatCharacter::execDoChargedAttackEnd },
		{ .NameUTF8 = UTF8TEXT("DoChargedAttackStart"), .Pointer = &ACombatCharacter::execDoChargedAttackStart },
		{ .NameUTF8 = UTF8TEXT("DoComboAttackEnd"), .Pointer = &ACombatCharacter::execDoComboAttackEnd },
		{ .NameUTF8 = UTF8TEXT("DoComboAttackStart"), .Pointer = &ACombatCharacter::execDoComboAttackStart },
		{ .NameUTF8 = UTF8TEXT("DoLook"), .Pointer = &ACombatCharacter::execDoLook },
		{ .NameUTF8 = UTF8TEXT("DoMove"), .Pointer = &ACombatCharacter::execDoMove },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatCharacter_BP_ToggleCamera, "BP_ToggleCamera" }, // 96dd015f0e6d2f627dbb6bcfa81c52a3f3b7efa7
		{ &Z_Construct_UFunction_ACombatCharacter_DealtDamage, "DealtDamage" }, // 6418fa87e1c56c6a9219d61b8b6a0d6f3a70045f
		{ &Z_Construct_UFunction_ACombatCharacter_DoChargedAttackEnd, "DoChargedAttackEnd" }, // eba565aef190695add1ffa97eee2a9c789dd1dd8
		{ &Z_Construct_UFunction_ACombatCharacter_DoChargedAttackStart, "DoChargedAttackStart" }, // 65b5987dfc06b2f19644fc5531dbf50aff513fc2
		{ &Z_Construct_UFunction_ACombatCharacter_DoComboAttackEnd, "DoComboAttackEnd" }, // c5c73641af4585cdbbfcd31d6a419ed67837f6c0
		{ &Z_Construct_UFunction_ACombatCharacter_DoComboAttackStart, "DoComboAttackStart" }, // 5140052574b2f6078a8404b7286c42a28d486458
		{ &Z_Construct_UFunction_ACombatCharacter_DoLook, "DoLook" }, // 216bd42f89e3016d7623185478a9bc98d941eaa1
		{ &Z_Construct_UFunction_ACombatCharacter_DoMove, "DoMove" }, // acf6f74bb1625b1553d29323c0251f87ee03ed27
		{ &Z_Construct_UFunction_ACombatCharacter_ReceivedDamage, "ReceivedDamage" }, // eaac34443a9ae65531afc7481e4b7539e7d772f7
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ACombatCharacter Property Definitions ************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LifeBar = { "LifeBar", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LifeBar), Z_Construct_UClass_UWidgetComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBar_MetaData), NewProp_LifeBar_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, JumpAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MoveAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LookAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MouseLookAction = { "MouseLookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MouseLookAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseLookAction_MetaData), NewProp_MouseLookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ComboAttackAction = { "ComboAttackAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboAttackAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboAttackAction_MetaData), NewProp_ComboAttackAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ChargedAttackAction = { "ChargedAttackAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargedAttackAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargedAttackAction_MetaData), NewProp_ChargedAttackAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ToggleCameraAction = { "ToggleCameraAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ToggleCameraAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ToggleCameraAction_MetaData), NewProp_ToggleCameraAction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MaxHP = { "MaxHP", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MaxHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxHP_MetaData), NewProp_MaxHP_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CurrentHP = { "CurrentHP", nullptr, (EPropertyFlags)0x0020080000020001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_LifeBarColor = { "LifeBarColor", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LifeBarColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBarColor_MetaData), NewProp_LifeBarColor_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_PelvisBoneName = { "PelvisBoneName", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, PelvisBoneName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PelvisBoneName_MetaData), NewProp_PelvisBoneName_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LifeBarWidget = { "LifeBarWidget", nullptr, (EPropertyFlags)0x0124080000080009, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, LifeBarWidget), Z_Construct_UClass_UCombatLifeBar, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifeBarWidget_MetaData), NewProp_LifeBarWidget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_AttackInputCacheTimeTolerance = { "AttackInputCacheTimeTolerance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, AttackInputCacheTimeTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackInputCacheTimeTolerance_MetaData), NewProp_AttackInputCacheTimeTolerance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeTraceDistance = { "MeleeTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeTraceDistance_MetaData), NewProp_MeleeTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeTraceRadius = { "MeleeTraceRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeTraceRadius_MetaData), NewProp_MeleeTraceRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DangerTraceDistance = { "DangerTraceDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, DangerTraceDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DangerTraceDistance_MetaData), NewProp_DangerTraceDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DangerTraceRadius = { "DangerTraceRadius", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, DangerTraceRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DangerTraceRadius_MetaData), NewProp_DangerTraceRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeDamage = { "MeleeDamage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeDamage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeDamage_MetaData), NewProp_MeleeDamage_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeKnockbackImpulse = { "MeleeKnockbackImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeKnockbackImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeKnockbackImpulse_MetaData), NewProp_MeleeKnockbackImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MeleeLaunchImpulse = { "MeleeLaunchImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, MeleeLaunchImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeleeLaunchImpulse_MetaData), NewProp_MeleeLaunchImpulse_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ComboAttackMontage = { "ComboAttackMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboAttackMontage), Z_Construct_UClass_UAnimMontage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboAttackMontage_MetaData), NewProp_ComboAttackMontage_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ComboSectionNames_Inner = { "ComboSectionNames", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ComboSectionNames = { "ComboSectionNames", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboSectionNames), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboSectionNames_MetaData), NewProp_ComboSectionNames_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ComboInputCacheTimeTolerance = { "ComboInputCacheTimeTolerance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ComboInputCacheTimeTolerance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ComboInputCacheTimeTolerance_MetaData), NewProp_ComboInputCacheTimeTolerance_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ChargedAttackMontage = { "ChargedAttackMontage", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargedAttackMontage), Z_Construct_UClass_UAnimMontage, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargedAttackMontage_MetaData), NewProp_ChargedAttackMontage_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ChargeLoopSection = { "ChargeLoopSection", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargeLoopSection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargeLoopSection_MetaData), NewProp_ChargeLoopSection_MetaData) };
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_ChargeAttackSection = { "ChargeAttackSection", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, ChargeAttackSection), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ChargeAttackSection_MetaData), NewProp_ChargeAttackSection_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeathCameraDistance = { "DeathCameraDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, DeathCameraDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathCameraDistance_MetaData), NewProp_DeathCameraDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DefaultCameraDistance = { "DefaultCameraDistance", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, DefaultCameraDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultCameraDistance_MetaData), NewProp_DefaultCameraDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RespawnTime = { "RespawnTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatCharacter, RespawnTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RespawnTime_MetaData), NewProp_RespawnTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LifeBar,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MouseLookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboAttackAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChargedAttackAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ToggleCameraAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MaxHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LifeBarColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PelvisBoneName,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LifeBarWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AttackInputCacheTimeTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeTraceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DangerTraceDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DangerTraceRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeDamage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeKnockbackImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MeleeLaunchImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboAttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboSectionNames_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboSectionNames,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ComboInputCacheTimeTolerance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChargedAttackMontage,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChargeLoopSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ChargeAttackSection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeathCameraDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultCameraDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RespawnTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ACombatCharacter Property Definitions **************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ACharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatAttacker, (int32)VTABLE_OFFSET(ACombatCharacter, ICombatAttacker), false },  // a9476cba592e946f33d8cdd21adabb99af57975c
	{ Z_Construct_UClass_UCombatDamageable, (int32)VTABLE_OFFSET(ACombatCharacter, ICombatDamageable), false },  // 7a4b5a8e7c3a75940e8ea3985c2adf6d465912d0
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ACombatCharacter,
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
static void ACombatCharacter_StaticRegisterNativesACombatCharacter()
{
	UClass* Class = ACombatCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatCharacter;
UClass* Z_Construct_UClass_ACombatCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ACombatCharacter;
		if (!Z_Registration_Info_UClass_ACombatCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatCharacter"),
				Z_Registration_Info_UClass_ACombatCharacter.InnerSingleton,
				ACombatCharacter_StaticRegisterNativesACombatCharacter,
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
		return Z_Registration_Info_UClass_ACombatCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ACombatCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatCharacter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ACombatCharacter);
ACombatCharacter::~ACombatCharacter() {}
// ********** End Class ACombatCharacter ***********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_CombatCharacter_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatCharacter, TEXT("ACombatCharacter"), &Z_Registration_Info_UClass_ACombatCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatCharacter), 2848743827U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_CombatCharacter_h__Script_DemoGame_648a3b9904d69a4ed2e112ed57588fbdc3cf5a55{
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
