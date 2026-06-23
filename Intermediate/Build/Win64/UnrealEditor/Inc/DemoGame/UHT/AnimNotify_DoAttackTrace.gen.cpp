// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnimNotify_DoAttackTrace.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeAnimNotify_DoAttackTrace() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UAnimNotify(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UAnimNotify_DoAttackTrace(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UAnimNotify_DoAttackTrace(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UAnimNotify_DoAttackTrace ************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UAnimNotify_DoAttackTrace_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  AnimNotify to tell the actor to perform an attack trace check to look for targets to damage.\n */" },
#endif
		{ "HideCategories", "Object" },
		{ "IncludePath", "Variant_Combat/Animation/AnimNotify_DoAttackTrace.h" },
		{ "ModuleRelativePath", "Variant_Combat/Animation/AnimNotify_DoAttackTrace.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "AnimNotify to tell the actor to perform an attack trace check to look for targets to damage." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackBoneName_MetaData[] = {
		{ "Category", "Attack" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Source bone for the attack trace */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Animation/AnimNotify_DoAttackTrace.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Source bone for the attack trace" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UAnimNotify_DoAttackTrace constinit property declarations ****************
	static const UECodeGen_Private::FNamePropertyParams NewProp_AttackBoneName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UAnimNotify_DoAttackTrace constinit property declarations ******************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnimNotify_DoAttackTrace>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class UAnimNotify_DoAttackTrace Property Definitions ***************************
const UECodeGen_Private::FNamePropertyParams UHT_STATICS::NewProp_AttackBoneName = { "AttackBoneName", nullptr, (EPropertyFlags)0x0020080000000011, UECodeGen_Private::EPropertyGenFlags::Name, nullptr, nullptr, 1, STRUCT_OFFSET(UAnimNotify_DoAttackTrace, AttackBoneName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackBoneName_MetaData), NewProp_AttackBoneName_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_AttackBoneName,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class UAnimNotify_DoAttackTrace Property Definitions *****************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UAnimNotify,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UAnimNotify_DoAttackTrace,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x000130A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace;
UClass* Z_Construct_UClass_UAnimNotify_DoAttackTrace(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UAnimNotify_DoAttackTrace;
		if (!Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("AnimNotify_DoAttackTrace"),
				Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.InnerSingleton,
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
		return Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace.OuterSingleton;
}
#undef UHT_STATICS
UAnimNotify_DoAttackTrace::UAnimNotify_DoAttackTrace(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UAnimNotify_DoAttackTrace);
UAnimNotify_DoAttackTrace::~UAnimNotify_DoAttackTrace() {}
// ********** End Class UAnimNotify_DoAttackTrace **************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Animation_AnimNotify_DoAttackTrace_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAnimNotify_DoAttackTrace, TEXT("UAnimNotify_DoAttackTrace"), &Z_Registration_Info_UClass_UAnimNotify_DoAttackTrace, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAnimNotify_DoAttackTrace), 3461605800U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Animation_AnimNotify_DoAttackTrace_h__Script_DemoGame_98421cb10ba4bea328354066cf3ca01c7ebd1886{
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
