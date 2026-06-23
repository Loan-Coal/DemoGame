// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimNotify_CheckChargedAttack.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeAnimNotify_CheckChargedAttack() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UAnimNotify_CheckChargedAttack(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UAnimNotify_CheckChargedAttack(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UAnimNotify_CheckChargedAttack *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UAnimNotify_CheckChargedAttack_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  AnimNotify to perform a charged attack hold check.\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "Variant_Combat/Animation/AnimNotify_CheckChargedAttack.h" },
		{ "ModuleRelativePath", "Variant_Combat/Animation/AnimNotify_CheckChargedAttack.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimNotify to perform a charged attack hold check." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UAnimNotify_CheckChargedAttack constinit property declarations ***********
// ********** End Class UAnimNotify_CheckChargedAttack constinit property declarations *************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimNotify_CheckChargedAttack>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UAnimNotify,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UAnimNotify_CheckChargedAttack,
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
FClassRegistrationInfo Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack;
UClass* Z_Construct_UClass_UAnimNotify_CheckChargedAttack(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UAnimNotify_CheckChargedAttack;
		if (!Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("AnimNotify_CheckChargedAttack"),
				Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack.InnerSingleton,
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
		return Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack.OuterSingleton;
}
#undef UHT_STATICS
UAnimNotify_CheckChargedAttack::UAnimNotify_CheckChargedAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UAnimNotify_CheckChargedAttack);
UAnimNotify_CheckChargedAttack::~UAnimNotify_CheckChargedAttack() {}
// ********** End Class UAnimNotify_CheckChargedAttack *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Animation_AnimNotify_CheckChargedAttack_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAnimNotify_CheckChargedAttack, TEXT("UAnimNotify_CheckChargedAttack"), &Z_Registration_Info_UClass_UAnimNotify_CheckChargedAttack, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimNotify_CheckChargedAttack), 545910009U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Animation_AnimNotify_CheckChargedAttack_h__Script_DemoGame_cf6642fb53cdf19c93f50ac9e8f8bf8a78a5d0d9{
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
