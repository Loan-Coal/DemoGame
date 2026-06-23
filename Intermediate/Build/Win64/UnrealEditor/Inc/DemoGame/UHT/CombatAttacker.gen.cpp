// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatAttacker.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatAttacker() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatAttacker(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatAttacker(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatAttacker(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatAttacker(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Interface UCombatAttacker Function CheckChargedAttack **************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs a charged attack's check to loop the charge animation. Usually called from a montage's AnimNotify */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs a charged attack's check to loop the charge animation. Usually called from a montage's AnimNotify" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CheckChargedAttack constinit property declarations ********************
// ********** End Function CheckChargedAttack constinit property declarations **********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatAttacker, nullptr, "CheckChargedAttack", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ICombatAttacker::execCheckChargedAttack)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckChargedAttack();
	P_NATIVE_END;
}
// ********** End Interface UCombatAttacker Function CheckChargedAttack ****************************

// ********** Begin Interface UCombatAttacker Function CheckCombo **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatAttacker_CheckCombo_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs a combo attack's check to continue the string. Usually called from a montage's AnimNotify */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs a combo attack's check to continue the string. Usually called from a montage's AnimNotify" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function CheckCombo constinit property declarations ****************************
// ********** End Function CheckCombo constinit property declarations ******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatAttacker, nullptr, "CheckCombo", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_UCombatAttacker_CheckCombo(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ICombatAttacker::execCheckCombo)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->CheckCombo();
	P_NATIVE_END;
}
// ********** End Interface UCombatAttacker Function CheckCombo ************************************

// ********** Begin Interface UCombatAttacker Function DoAttackTrace *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatAttacker_DoAttackTrace_Statics
struct UHT_STATICS
{
	struct CombatAttacker_eventDoAttackTrace_Parms
	{
		FName DamageSourceBone;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Attacker" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Performs an attack's collision check. Usually called from a montage's AnimNotify */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Performs an attack's collision check. Usually called from a montage's AnimNotify" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoAttackTrace constinit property declarations *************************
	static const UECodeGen_Private::FNamePropertyParams NewProp_DamageSourceBone;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoAttackTrace constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoAttackTrace Property Definitions ************************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_DamageSourceBone = { "DamageSourceBone", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(CombatAttacker_eventDoAttackTrace_Parms, DamageSourceBone), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DamageSourceBone,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoAttackTrace Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatAttacker, nullptr, "DoAttackTrace", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatAttacker_eventDoAttackTrace_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatAttacker_eventDoAttackTrace_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatAttacker_DoAttackTrace(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ICombatAttacker::execDoAttackTrace)
{
	P_GET_PROPERTY(FNameProperty,Z_Param_DamageSourceBone);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoAttackTrace(Z_Param_DamageSourceBone);
	P_NATIVE_END;
}
// ********** End Interface UCombatAttacker Function DoAttackTrace *********************************

// ********** Begin Interface UCombatAttacker ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UCombatAttacker_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatAttacker.h" },
	};
#endif // WITH_METADATA

// ********** Begin Interface UCombatAttacker constinit property declarations **********************
// ********** End Interface UCombatAttacker constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("CheckChargedAttack"), .Pointer = &ICombatAttacker::execCheckChargedAttack },
		{ .NameUTF8 = UTF8TEXT("CheckCombo"), .Pointer = &ICombatAttacker::execCheckCombo },
		{ .NameUTF8 = UTF8TEXT("DoAttackTrace"), .Pointer = &ICombatAttacker::execDoAttackTrace },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCombatAttacker_CheckChargedAttack, "CheckChargedAttack" }, // 24ca973e3f9fe76beac87ff04add3b2053997e5b
		{ &Z_Construct_UFunction_UCombatAttacker_CheckCombo, "CheckCombo" }, // e7f16e152a90b0b58e863c37adcc7535f9eb7bce
		{ &Z_Construct_UFunction_UCombatAttacker_DoAttackTrace, "DoAttackTrace" }, // c47d7cf4c21539b535650b6a2a8090886aafb0fe
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ICombatAttacker>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UInterface,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UCombatAttacker,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000840A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void UCombatAttacker_StaticRegisterNativesUCombatAttacker()
{
	UClass* Class = UCombatAttacker::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCombatAttacker;
UClass* Z_Construct_UClass_UCombatAttacker(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UCombatAttacker;
		if (!Z_Registration_Info_UClass_UCombatAttacker.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatAttacker"),
				Z_Registration_Info_UClass_UCombatAttacker.InnerSingleton,
				UCombatAttacker_StaticRegisterNativesUCombatAttacker,
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
		return Z_Registration_Info_UClass_UCombatAttacker.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UCombatAttacker.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCombatAttacker.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UCombatAttacker.OuterSingleton;
}
#undef UHT_STATICS
UCombatAttacker::UCombatAttacker(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UCombatAttacker);
// ********** End Interface UCombatAttacker ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Interfaces_CombatAttacker_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCombatAttacker, TEXT("UCombatAttacker"), &Z_Registration_Info_UClass_UCombatAttacker, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCombatAttacker), 2840030394U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Interfaces_CombatAttacker_h__Script_DemoGame_35423ac39b76f769f4b5320d83f5eed9c420aaa4{
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
