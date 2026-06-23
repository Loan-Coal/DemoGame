// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimNotify_EndDash.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeAnimNotify_EndDash() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UAnimNotify_EndDash(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UAnimNotify_EndDash(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UAnimNotify_EndDash ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UAnimNotify_EndDash_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  AnimNotify to finish the dash animation and restore player control\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "Variant_Platforming/Animation/AnimNotify_EndDash.h" },
		{ "ModuleRelativePath", "Variant_Platforming/Animation/AnimNotify_EndDash.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimNotify to finish the dash animation and restore player control" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UAnimNotify_EndDash constinit property declarations **********************
// ********** End Class UAnimNotify_EndDash constinit property declarations ************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimNotify_EndDash>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UAnimNotify,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UAnimNotify_EndDash,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x000130A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UAnimNotify_EndDash;
UClass* Z_Construct_UClass_UAnimNotify_EndDash(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UAnimNotify_EndDash;
		if (!Z_Registration_Info_UClass_UAnimNotify_EndDash.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("AnimNotify_EndDash"),
				Z_Registration_Info_UClass_UAnimNotify_EndDash.InnerSingleton,
				nullptr,
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
		return Z_Registration_Info_UClass_UAnimNotify_EndDash.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UAnimNotify_EndDash.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimNotify_EndDash.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnimNotify_EndDash.OuterSingleton;
}
#undef UHT_STATICS
UAnimNotify_EndDash::UAnimNotify_EndDash(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UAnimNotify_EndDash);
UAnimNotify_EndDash::~UAnimNotify_EndDash() {}
// ********** End Class UAnimNotify_EndDash ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Platforming_Animation_AnimNotify_EndDash_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAnimNotify_EndDash, TEXT("UAnimNotify_EndDash"), &Z_Registration_Info_UClass_UAnimNotify_EndDash, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimNotify_EndDash), 1612278121U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Platforming_Animation_AnimNotify_EndDash_h__Script_DemoGame_a52b73862a47350621d3b0ea4cc348a9099ddbc0{
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
