// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingCameraManager.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingCameraManager() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerCameraManager(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingCameraManager(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingCameraManager(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingCameraManager **********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingCameraManager_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple side scrolling camera with smooth scrolling and horizontal bounds\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple side scrolling camera with smooth scrolling and horizontal bounds" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentZoom_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How close we want to stay to the view target */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How close we want to stay to the view target" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraZOffset_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** How far above the target do we want the camera to focus */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "How far above the target do we want the camera to focus" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraXMinBounds_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "100000" },
		{ "ClampMin", "-100000" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Minimum camera scrolling bounds in world space */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Minimum camera scrolling bounds in world space" },
#endif
		{ "Units", "cm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraXMaxBounds_MetaData[] = {
		{ "Category", "Side Scrolling Camera" },
		{ "ClampMax", "100000" },
		{ "ClampMin", "-100000" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Maximum camera scrolling bounds in world space */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingCameraManager.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Maximum camera scrolling bounds in world space" },
#endif
		{ "Units", "cm" },
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingCameraManager constinit property declarations **************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentZoom;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraZOffset;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraXMinBounds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CameraXMaxBounds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingCameraManager constinit property declarations ****************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingCameraManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingCameraManager Property Definitions *************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CurrentZoom = { "CurrentZoom", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CurrentZoom), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentZoom_MetaData), NewProp_CurrentZoom_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CameraZOffset = { "CameraZOffset", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CameraZOffset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraZOffset_MetaData), NewProp_CameraZOffset_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CameraXMinBounds = { "CameraXMinBounds", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CameraXMinBounds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraXMinBounds_MetaData), NewProp_CameraXMinBounds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CameraXMaxBounds = { "CameraXMaxBounds", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingCameraManager, CameraXMaxBounds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraXMaxBounds_MetaData), NewProp_CameraXMaxBounds_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentZoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CameraZOffset,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CameraXMinBounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CameraXMaxBounds,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingCameraManager Property Definitions ***************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_APlayerCameraManager,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingCameraManager,
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
	0x008002ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingCameraManager;
UClass* Z_Construct_UClass_ASideScrollingCameraManager(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingCameraManager;
		if (!Z_Registration_Info_UClass_ASideScrollingCameraManager.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingCameraManager"),
				Z_Registration_Info_UClass_ASideScrollingCameraManager.InnerSingleton,
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
		return Z_Registration_Info_UClass_ASideScrollingCameraManager.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingCameraManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingCameraManager.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingCameraManager.OuterSingleton;
}
#undef UHT_STATICS
ASideScrollingCameraManager::ASideScrollingCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingCameraManager);
ASideScrollingCameraManager::~ASideScrollingCameraManager() {}
// ********** End Class ASideScrollingCameraManager ************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingCameraManager_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingCameraManager, TEXT("ASideScrollingCameraManager"), &Z_Registration_Info_UClass_ASideScrollingCameraManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingCameraManager), 1748764004U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingCameraManager_h__Script_DemoGame_af045c9b2ca7b8882eb3a9b22f537a36e2f8637f{
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
