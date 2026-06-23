// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingJumpPad.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingJumpPad() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingJumpPad(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingJumpPad(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingJumpPad Function BeginOverlap ******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingJumpPad_BeginOverlap_Statics
struct UHT_STATICS
{
	struct SideScrollingJumpPad_eventBeginOverlap_Parms
	{
		AActor* OverlappedActor;
		AActor* OtherActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingJumpPad.h" },
	};
#endif // WITH_METADATA

// ********** Begin Function BeginOverlap constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BeginOverlap constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BeginOverlap Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OverlappedActor = { "OverlappedActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingJumpPad_eventBeginOverlap_Parms, OverlappedActor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingJumpPad_eventBeginOverlap_Parms, OtherActor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OverlappedActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OtherActor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BeginOverlap Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingJumpPad, nullptr, "BeginOverlap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingJumpPad_eventBeginOverlap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingJumpPad_eventBeginOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingJumpPad_BeginOverlap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingJumpPad::execBeginOverlap)
{
	P_GET_OBJECT(AActor,Z_Param_OverlappedActor);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BeginOverlap(Z_Param_OverlappedActor,Z_Param_OtherActor);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingJumpPad Function BeginOverlap ********************************

// ********** Begin Class ASideScrollingJumpPad ****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingJumpPad_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple jump pad that launches characters into the air\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/Gameplay/SideScrollingJumpPad.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingJumpPad.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple jump pad that launches characters into the air" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Box_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump pad bounding box */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingJumpPad.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump pad bounding box" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ZStrength_MetaData[] = {
		{ "Category", "Jump Pad" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Vertical velocity to set the character to when they use the jump pad */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingJumpPad.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Vertical velocity to set the character to when they use the jump pad" },
#endif
		{ "Units", "cm/s" },
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingJumpPad constinit property declarations ********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Box;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ZStrength;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingJumpPad constinit property declarations **********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("BeginOverlap"), .Pointer = &ASideScrollingJumpPad::execBeginOverlap },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingJumpPad_BeginOverlap, "BeginOverlap" }, // 2389b210eb30271678218ca9a3b60540fa130287
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingJumpPad>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingJumpPad Property Definitions *******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Box = { "Box", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingJumpPad, Box), Z_Construct_UClass_UBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Box_MetaData), NewProp_Box_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ZStrength = { "ZStrength", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingJumpPad, ZStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ZStrength_MetaData), NewProp_ZStrength_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Box,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ZStrength,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingJumpPad Property Definitions *********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingJumpPad,
	"Engine",
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
static void ASideScrollingJumpPad_StaticRegisterNativesASideScrollingJumpPad()
{
	UClass* Class = ASideScrollingJumpPad::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingJumpPad;
UClass* Z_Construct_UClass_ASideScrollingJumpPad(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingJumpPad;
		if (!Z_Registration_Info_UClass_ASideScrollingJumpPad.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingJumpPad"),
				Z_Registration_Info_UClass_ASideScrollingJumpPad.InnerSingleton,
				ASideScrollingJumpPad_StaticRegisterNativesASideScrollingJumpPad,
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
		return Z_Registration_Info_UClass_ASideScrollingJumpPad.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingJumpPad.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingJumpPad.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingJumpPad.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingJumpPad);
ASideScrollingJumpPad::~ASideScrollingJumpPad() {}
// ********** End Class ASideScrollingJumpPad ******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingJumpPad_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingJumpPad, TEXT("ASideScrollingJumpPad"), &Z_Registration_Info_UClass_ASideScrollingJumpPad, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingJumpPad), 1674030241U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingJumpPad_h__Script_DemoGame_b993980e21b66e95bfcbd8e749982baeb3562236{
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
