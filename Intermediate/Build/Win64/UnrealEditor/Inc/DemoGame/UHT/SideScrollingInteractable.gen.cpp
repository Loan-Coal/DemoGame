// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingInteractable.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingInteractable() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UInterface(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_USideScrollingInteractable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ISideScrollingInteractable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_USideScrollingInteractable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ISideScrollingInteractable(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Interface USideScrollingInteractable Function Interaction **********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_USideScrollingInteractable_Interaction_Statics
struct UHT_STATICS
{
	struct SideScrollingInteractable_eventInteraction_Parms
	{
		AActor* Interactor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Interactable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Triggers an interaction by the provided Actor */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Interfaces/SideScrollingInteractable.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Triggers an interaction by the provided Actor" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function Interaction constinit property declarations ***************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Interactor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function Interaction constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function Interaction Property Definitions **************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Interactor = { "Interactor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingInteractable_eventInteraction_Parms, Interactor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Interactor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function Interaction Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_USideScrollingInteractable, nullptr, "Interaction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingInteractable_eventInteraction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingInteractable_eventInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USideScrollingInteractable_Interaction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ISideScrollingInteractable::execInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_Interactor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Interaction(Z_Param_Interactor);
	P_NATIVE_END;
}
// ********** End Interface USideScrollingInteractable Function Interaction ************************

// ********** Begin Interface USideScrollingInteractable *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_USideScrollingInteractable_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "IsBlueprintBase", "false" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Interfaces/SideScrollingInteractable.h" },
	};
#endif // WITH_METADATA

// ********** Begin Interface USideScrollingInteractable constinit property declarations ***********
// ********** End Interface USideScrollingInteractable constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("Interaction"), .Pointer = &ISideScrollingInteractable::execInteraction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USideScrollingInteractable_Interaction, "Interaction" }, // 695ab4e3fc79e1cf6d584755073e947b70e18889
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ISideScrollingInteractable>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UInterface,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_USideScrollingInteractable,
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
static void USideScrollingInteractable_StaticRegisterNativesUSideScrollingInteractable()
{
	UClass* Class = USideScrollingInteractable::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_USideScrollingInteractable;
UClass* Z_Construct_UClass_USideScrollingInteractable(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = USideScrollingInteractable;
		if (!Z_Registration_Info_UClass_USideScrollingInteractable.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingInteractable"),
				Z_Registration_Info_UClass_USideScrollingInteractable.InnerSingleton,
				USideScrollingInteractable_StaticRegisterNativesUSideScrollingInteractable,
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
		return Z_Registration_Info_UClass_USideScrollingInteractable.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_USideScrollingInteractable.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USideScrollingInteractable.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_USideScrollingInteractable.OuterSingleton;
}
#undef UHT_STATICS
USideScrollingInteractable::USideScrollingInteractable(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, USideScrollingInteractable);
// ********** End Interface USideScrollingInteractable *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Interfaces_SideScrollingInteractable_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USideScrollingInteractable, TEXT("USideScrollingInteractable"), &Z_Registration_Info_UClass_USideScrollingInteractable, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USideScrollingInteractable), 380176163U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Interfaces_SideScrollingInteractable_h__Script_DemoGame_2dd3d49b09ab4dcb157b35cf266c98068ad31027{
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
