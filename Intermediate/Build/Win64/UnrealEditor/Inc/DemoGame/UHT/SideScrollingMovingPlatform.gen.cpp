// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingMovingPlatform.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingMovingPlatform() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingMovingPlatform(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ISideScrollingInteractable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingMovingPlatform(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingMovingPlatform Function BP_MoveToTarget ********************
static FName NAME_ASideScrollingMovingPlatform_BP_MoveToTarget = FName(TEXT("BP_MoveToTarget"));
void ASideScrollingMovingPlatform::BP_MoveToTarget()
{
	UFunction* Func = FindFunctionChecked(NAME_ASideScrollingMovingPlatform_BP_MoveToTarget);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Allows Blueprint code to do the actual platform movement */" },
#endif
		{ "DisplayName", "Move to Target" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Allows Blueprint code to do the actual platform movement" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_MoveToTarget constinit property declarations ***********************
// ********** End Function BP_MoveToTarget constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingMovingPlatform, nullptr, "BP_MoveToTarget", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x0C080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ASideScrollingMovingPlatform Function BP_MoveToTarget **********************

// ********** Begin Class ASideScrollingMovingPlatform Function ResetInteraction *******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Resets the interaction state. Must be called from BP code to reset the platform */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Resets the interaction state. Must be called from BP code to reset the platform" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ResetInteraction constinit property declarations **********************
// ********** End Function ResetInteraction constinit property declarations ************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingMovingPlatform, nullptr, "ResetInteraction", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingMovingPlatform::execResetInteraction)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ResetInteraction();
	P_NATIVE_END;
}
// ********** End Class ASideScrollingMovingPlatform Function ResetInteraction *********************

// ********** Begin Class ASideScrollingMovingPlatform *********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingMovingPlatform_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple moving platform that can be triggered through interactions by other actors.\n *  The actual movement is performed by Blueprint code through latent execution nodes.\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple moving platform that can be triggered through interactions by other actors.\nThe actual movement is performed by Blueprint code through latent execution nodes." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PlatformTarget_MetaData[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Destination of the platform in world space */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Destination of the platform in world space" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveDuration_MetaData[] = {
		{ "Category", "Moving Platform" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time for the platform to move to the destination */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time for the platform to move to the destination" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bOneShot_MetaData[] = {
		{ "Category", "Moving Platform" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If this is true, the platform will only move once. */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingMovingPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If this is true, the platform will only move once." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingMovingPlatform constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_PlatformTarget;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MoveDuration;
	static void NewProp_bOneShot_SetBit(void* Obj)
	{
		((ASideScrollingMovingPlatform*)Obj)->bOneShot = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bOneShot;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingMovingPlatform constinit property declarations ***************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ResetInteraction"), .Pointer = &ASideScrollingMovingPlatform::execResetInteraction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingMovingPlatform_BP_MoveToTarget, "BP_MoveToTarget" }, // 6438a14d225ceafd636e4937d713acfdd7436858
		{ &Z_Construct_UFunction_ASideScrollingMovingPlatform_ResetInteraction, "ResetInteraction" }, // 1432e4674bb7a87327bcc9427be0a43844672a16
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingMovingPlatform>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingMovingPlatform Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_PlatformTarget = { "PlatformTarget", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingMovingPlatform, PlatformTarget), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PlatformTarget_MetaData), NewProp_PlatformTarget_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_MoveDuration = { "MoveDuration", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingMovingPlatform, MoveDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveDuration_MetaData), NewProp_MoveDuration_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bOneShot = { "bOneShot", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ASideScrollingMovingPlatform), &UHT_STATICS::NewProp_bOneShot_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bOneShot_MetaData), NewProp_bOneShot_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PlatformTarget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MoveDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bOneShot,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingMovingPlatform Property Definitions **************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_USideScrollingInteractable, (int32)VTABLE_OFFSET(ASideScrollingMovingPlatform, ISideScrollingInteractable), false },  // 16a90723bd7e749750935d50cae1ea5a1ab3a753
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingMovingPlatform,
	"Engine",
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
static void ASideScrollingMovingPlatform_StaticRegisterNativesASideScrollingMovingPlatform()
{
	UClass* Class = ASideScrollingMovingPlatform::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingMovingPlatform;
UClass* Z_Construct_UClass_ASideScrollingMovingPlatform(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingMovingPlatform;
		if (!Z_Registration_Info_UClass_ASideScrollingMovingPlatform.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingMovingPlatform"),
				Z_Registration_Info_UClass_ASideScrollingMovingPlatform.InnerSingleton,
				ASideScrollingMovingPlatform_StaticRegisterNativesASideScrollingMovingPlatform,
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
		return Z_Registration_Info_UClass_ASideScrollingMovingPlatform.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingMovingPlatform.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingMovingPlatform.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingMovingPlatform.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingMovingPlatform);
ASideScrollingMovingPlatform::~ASideScrollingMovingPlatform() {}
// ********** End Class ASideScrollingMovingPlatform ***********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingMovingPlatform_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingMovingPlatform, TEXT("ASideScrollingMovingPlatform"), &Z_Registration_Info_UClass_ASideScrollingMovingPlatform, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingMovingPlatform), 391658082U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingMovingPlatform_h__Script_DemoGame_b6dab678aa4067e9a75367905bda98e524f58f97{
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
