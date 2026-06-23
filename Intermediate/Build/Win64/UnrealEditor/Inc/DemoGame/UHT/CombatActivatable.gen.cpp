// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatActivatable.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatActivatable() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatActivatable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatActivatable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatActivatable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatActivatable(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Interface UCombatActivatable Function ActivateInteraction **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatActivatable_ActivateInteraction_Statics
struct UHT_STATICS
{
	struct CombatActivatable_eventActivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Activates the Interactable Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Activates the Interactable Actor" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ActivateInteraction constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ActivateInteraction constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ActivateInteraction Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(CombatActivatable_eventActivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ActivateInteraction Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatActivatable, nullptr, "ActivateInteraction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatActivatable_eventActivateInteraction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatActivatable_eventActivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatActivatable_ActivateInteraction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ICombatActivatable::execActivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ActivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Interface UCombatActivatable Function ActivateInteraction ************************

// ********** Begin Interface UCombatActivatable Function DeactivateInteraction ********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction_Statics
struct UHT_STATICS
{
	struct CombatActivatable_eventDeactivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deactivates the Interactable Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deactivates the Interactable Actor" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DeactivateInteraction constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeactivateInteraction constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeactivateInteraction Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(CombatActivatable_eventDeactivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeactivateInteraction Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatActivatable, nullptr, "DeactivateInteraction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatActivatable_eventDeactivateInteraction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatActivatable_eventDeactivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ICombatActivatable::execDeactivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DeactivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Interface UCombatActivatable Function DeactivateInteraction **********************

// ********** Begin Interface UCombatActivatable Function ToggleInteraction ************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatActivatable_ToggleInteraction_Statics
struct UHT_STATICS
{
	struct CombatActivatable_eventToggleInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Toggles the Interactable Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Toggles the Interactable Actor" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ToggleInteraction constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ToggleInteraction constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ToggleInteraction Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(CombatActivatable_eventToggleInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ToggleInteraction Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatActivatable, nullptr, "ToggleInteraction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatActivatable_eventToggleInteraction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatActivatable_eventToggleInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatActivatable_ToggleInteraction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ICombatActivatable::execToggleInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Interface UCombatActivatable Function ToggleInteraction **************************

// ********** Begin Interface UCombatActivatable ***************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UCombatActivatable_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Variant_Combat/Interfaces/CombatActivatable.h" },
	};
#endif // WITH_METADATA

// ********** Begin Interface UCombatActivatable constinit property declarations *******************
// ********** End Interface UCombatActivatable constinit property declarations *********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ActivateInteraction"), .Pointer = &ICombatActivatable::execActivateInteraction },
		{ .NameUTF8 = UTF8TEXT("DeactivateInteraction"), .Pointer = &ICombatActivatable::execDeactivateInteraction },
		{ .NameUTF8 = UTF8TEXT("ToggleInteraction"), .Pointer = &ICombatActivatable::execToggleInteraction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCombatActivatable_ActivateInteraction, "ActivateInteraction" }, // 20ee19862ff15700e72cce8a85c23b3025264b6e
		{ &Z_Construct_UFunction_UCombatActivatable_DeactivateInteraction, "DeactivateInteraction" }, // e3b32594f9f4b7570da81bc5c18d6b179e19fdfd
		{ &Z_Construct_UFunction_UCombatActivatable_ToggleInteraction, "ToggleInteraction" }, // f119d0af655a9d07dc7cfd5d2bf4ace6b093b2a1
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ICombatActivatable>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UInterface,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UCombatActivatable,
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
static void UCombatActivatable_StaticRegisterNativesUCombatActivatable()
{
	UClass* Class = UCombatActivatable::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UCombatActivatable;
UClass* Z_Construct_UClass_UCombatActivatable(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UCombatActivatable;
		if (!Z_Registration_Info_UClass_UCombatActivatable.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatActivatable"),
				Z_Registration_Info_UClass_UCombatActivatable.InnerSingleton,
				UCombatActivatable_StaticRegisterNativesUCombatActivatable,
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
		return Z_Registration_Info_UClass_UCombatActivatable.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UCombatActivatable.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCombatActivatable.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UCombatActivatable.OuterSingleton;
}
#undef UHT_STATICS
UCombatActivatable::UCombatActivatable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UCombatActivatable);
// ********** End Interface UCombatActivatable *****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Interfaces_CombatActivatable_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCombatActivatable, TEXT("UCombatActivatable"), &Z_Registration_Info_UClass_UCombatActivatable, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCombatActivatable), 2985222400U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Interfaces_CombatActivatable_h__Script_DemoGame_c4cbcb930d71db3e04df5efbbe213785717c12e5{
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
