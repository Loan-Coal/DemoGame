// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingPlayerController() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerController(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputMappingContext(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingPlayerController(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingCharacter(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingPlayerController(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingPlayerController Function OnPawnDestroyed ******************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed_Statics
struct UHT_STATICS
{
	struct SideScrollingPlayerController_eventOnPawnDestroyed_Parms
	{
		AActor* DestroyedActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called if the possessed pawn is destroyed */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called if the possessed pawn is destroyed" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnPawnDestroyed constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DestroyedActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnPawnDestroyed constinit property declarations *************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnPawnDestroyed Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DestroyedActor = { "DestroyedActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingPlayerController_eventOnPawnDestroyed_Parms, DestroyedActor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DestroyedActor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function OnPawnDestroyed Property Definitions ************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingPlayerController, nullptr, "OnPawnDestroyed", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingPlayerController_eventOnPawnDestroyed_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingPlayerController_eventOnPawnDestroyed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingPlayerController::execOnPawnDestroyed)
{
	P_GET_OBJECT(AActor,Z_Param_DestroyedActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnPawnDestroyed(Z_Param_DestroyedActor);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingPlayerController Function OnPawnDestroyed ********************

// ********** Begin Class ASideScrollingPlayerController *******************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingPlayerController_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple Side Scrolling Player Controller\n *  Manages input mappings\n *  Respawns the player pawn at the player start if it is destroyed\n */" },
#endif
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple Side Scrolling Player Controller\nManages input mappings\nRespawns the player pawn at the player start if it is destroyed" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultMappingContexts_MetaData[] = {
		{ "Category", "Input|Input Mappings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input mapping context for this player */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input mapping context for this player" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MobileExcludedMappingContexts_MetaData[] = {
		{ "Category", "Input|Input Mappings" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Input Mapping Contexts */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Input Mapping Contexts" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MobileControlsWidgetClass_MetaData[] = {
		{ "Category", "Input|Touch Controls" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mobile controls widget to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mobile controls widget to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MobileControlsWidget_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pointer to the mobile controls widget */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pointer to the mobile controls widget" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bForceTouchControls_MetaData[] = {
		{ "Category", "Input|Touch Controls" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the player will use UMG touch controls even if not playing on mobile platforms */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the player will use UMG touch controls even if not playing on mobile platforms" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CharacterClass_MetaData[] = {
		{ "Category", "Respawn" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Character class to respawn when the possessed pawn is destroyed */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingPlayerController.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Character class to respawn when the possessed pawn is destroyed" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingPlayerController constinit property declarations ***********
	static const UECodeGen_Private::FObjectPropertyParams NewProp_DefaultMappingContexts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_DefaultMappingContexts;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MobileExcludedMappingContexts_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MobileExcludedMappingContexts;
	static const UECodeGen_Private::FClassPropertyParams NewProp_MobileControlsWidgetClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MobileControlsWidget;
	static void NewProp_bForceTouchControls_SetBit(void* Obj)
	{
		((ASideScrollingPlayerController*)Obj)->bForceTouchControls = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bForceTouchControls;
	static const UECodeGen_Private::FClassPropertyParams NewProp_CharacterClass;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingPlayerController constinit property declarations *************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnPawnDestroyed"), .Pointer = &ASideScrollingPlayerController::execOnPawnDestroyed },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingPlayerController_OnPawnDestroyed, "OnPawnDestroyed" }, // 64dc18d8447c1b3ab1df9b6bce813a0e3990ef1c
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingPlayerController Property Definitions **********************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_DefaultMappingContexts_Inner = { "DefaultMappingContexts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInputMappingContext, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_DefaultMappingContexts = { "DefaultMappingContexts", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, DefaultMappingContexts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultMappingContexts_MetaData), NewProp_DefaultMappingContexts_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MobileExcludedMappingContexts_Inner = { "MobileExcludedMappingContexts", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, 0, Z_Construct_UClass_UInputMappingContext, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_MobileExcludedMappingContexts = { "MobileExcludedMappingContexts", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, MobileExcludedMappingContexts), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MobileExcludedMappingContexts_MetaData), NewProp_MobileExcludedMappingContexts_MetaData) };
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_MobileControlsWidgetClass = { "MobileControlsWidgetClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, MobileControlsWidgetClass), Z_Construct_UClass_UClass, Z_Construct_UClass_UUserWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MobileControlsWidgetClass_MetaData), NewProp_MobileControlsWidgetClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MobileControlsWidget = { "MobileControlsWidget", nullptr, (EPropertyFlags)0x0124080000080008, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, MobileControlsWidget), Z_Construct_UClass_UUserWidget, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MobileControlsWidget_MetaData), NewProp_MobileControlsWidget_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bForceTouchControls = { "bForceTouchControls", nullptr, (EPropertyFlags)0x0020080000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ASideScrollingPlayerController), &UHT_STATICS::NewProp_bForceTouchControls_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bForceTouchControls_MetaData), NewProp_bForceTouchControls_MetaData) };
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_CharacterClass = { "CharacterClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPlayerController, CharacterClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ASideScrollingCharacter, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CharacterClass_MetaData), NewProp_CharacterClass_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultMappingContexts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DefaultMappingContexts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MobileExcludedMappingContexts_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MobileExcludedMappingContexts,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MobileControlsWidgetClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MobileControlsWidget,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bForceTouchControls,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CharacterClass,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingPlayerController Property Definitions ************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_APlayerController,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingPlayerController,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x008002A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ASideScrollingPlayerController_StaticRegisterNativesASideScrollingPlayerController()
{
	UClass* Class = ASideScrollingPlayerController::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingPlayerController;
UClass* Z_Construct_UClass_ASideScrollingPlayerController(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingPlayerController;
		if (!Z_Registration_Info_UClass_ASideScrollingPlayerController.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingPlayerController"),
				Z_Registration_Info_UClass_ASideScrollingPlayerController.InnerSingleton,
				ASideScrollingPlayerController_StaticRegisterNativesASideScrollingPlayerController,
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
		return Z_Registration_Info_UClass_ASideScrollingPlayerController.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingPlayerController.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingPlayerController.OuterSingleton;
}
#undef UHT_STATICS
ASideScrollingPlayerController::ASideScrollingPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingPlayerController);
ASideScrollingPlayerController::~ASideScrollingPlayerController() {}
// ********** End Class ASideScrollingPlayerController *********************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingPlayerController_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingPlayerController, TEXT("ASideScrollingPlayerController"), &Z_Registration_Info_UClass_ASideScrollingPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingPlayerController), 1837804434U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingPlayerController_h__Script_DemoGame_0326cebd6f4a390a3643fe53177c13d02e7eb71f{
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
