// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingAIController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingAIController() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_AAIController(ETypeConstructPhase);
GAMEPLAYSTATETREEMODULE_API UClass* Z_Construct_UClass_UStateTreeAIComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingAIController(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingAIController(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingAIController ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingAIController_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A basic AI Controller capable of running StateTree\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Variant_SideScrolling/AI/SideScrollingAIController.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic AI Controller capable of running StateTree" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_StateTreeAI_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "AI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** StateTree Component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingAIController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "StateTree Component" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingAIController constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_StateTreeAI;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingAIController constinit property declarations *****************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingAIController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingAIController Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_StateTreeAI = { "StateTreeAI", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingAIController, StateTreeAI), Z_Construct_UClass_UStateTreeAIComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_StateTreeAI_MetaData), NewProp_StateTreeAI_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_StateTreeAI,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingAIController Property Definitions ****************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AAIController,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingAIController,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x008002A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingAIController;
UClass* Z_Construct_UClass_ASideScrollingAIController(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingAIController;
		if (!Z_Registration_Info_UClass_ASideScrollingAIController.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingAIController"),
				Z_Registration_Info_UClass_ASideScrollingAIController.InnerSingleton,
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
		return Z_Registration_Info_UClass_ASideScrollingAIController.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingAIController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingAIController.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingAIController.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingAIController);
ASideScrollingAIController::~ASideScrollingAIController() {}
// ********** End Class ASideScrollingAIController *************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_AI_SideScrollingAIController_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingAIController, TEXT("ASideScrollingAIController"), &Z_Registration_Info_UClass_ASideScrollingAIController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingAIController), 1426132948U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_AI_SideScrollingAIController_h__Script_DemoGame_60c28169fc9eec3f3b07d89642e7b1b66de045f7{
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
