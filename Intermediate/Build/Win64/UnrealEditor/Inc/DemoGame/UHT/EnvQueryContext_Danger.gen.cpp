// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EnvQueryContext_Danger.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeEnvQueryContext_Danger() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UEnvQueryContext(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UEnvQueryContext_Danger(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UEnvQueryContext_Danger(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UEnvQueryContext_Danger **************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UEnvQueryContext_Danger_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  UEnvQueryContext_Danger\n *  Returns the enemy character's last known danger location\n */" },
#endif
		{ "IncludePath", "Variant_Combat/AI/EnvQueryContext_Danger.h" },
		{ "ModuleRelativePath", "Variant_Combat/AI/EnvQueryContext_Danger.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UEnvQueryContext_Danger\nReturns the enemy character's last known danger location" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UEnvQueryContext_Danger constinit property declarations ******************
// ********** End Class UEnvQueryContext_Danger constinit property declarations ********************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UEnvQueryContext_Danger>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UEnvQueryContext,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UEnvQueryContext_Danger,
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
	0x001010A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UEnvQueryContext_Danger;
UClass* Z_Construct_UClass_UEnvQueryContext_Danger(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UEnvQueryContext_Danger;
		if (!Z_Registration_Info_UClass_UEnvQueryContext_Danger.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("EnvQueryContext_Danger"),
				Z_Registration_Info_UClass_UEnvQueryContext_Danger.InnerSingleton,
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
		return Z_Registration_Info_UClass_UEnvQueryContext_Danger.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UEnvQueryContext_Danger.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UEnvQueryContext_Danger.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UEnvQueryContext_Danger.OuterSingleton;
}
#undef UHT_STATICS
UEnvQueryContext_Danger::UEnvQueryContext_Danger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UEnvQueryContext_Danger);
UEnvQueryContext_Danger::~UEnvQueryContext_Danger() {}
// ********** End Class UEnvQueryContext_Danger ****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_EnvQueryContext_Danger_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UEnvQueryContext_Danger, TEXT("UEnvQueryContext_Danger"), &Z_Registration_Info_UClass_UEnvQueryContext_Danger, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UEnvQueryContext_Danger), 1836299860U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_EnvQueryContext_Danger_h__Script_DemoGame_5fa69d4884ede8b099cb1530a20bd861846c20a7{
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
