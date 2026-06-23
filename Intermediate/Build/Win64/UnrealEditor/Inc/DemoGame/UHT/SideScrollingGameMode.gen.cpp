// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingGameMode(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingGameMode(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_USideScrollingUI(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingGameMode ***************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingGameMode_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple Side Scrolling Game Mode\n *  Spawns and manages the game UI\n *  Counts pickups collected by the player\n */" },
#endif
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple Side Scrolling Game Mode\nSpawns and manages the game UI\nCounts pickups collected by the player" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserInterfaceClass_MetaData[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Class of UI widget to spawn when the game starts */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Class of UI widget to spawn when the game starts" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UserInterface_MetaData[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** User interface widget for the game */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "User interface widget for the game" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PickupsCollected_MetaData[] = {
		{ "Category", "Pickups" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of pickups collected by the player */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of pickups collected by the player" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NumberOfLocalPlayers_MetaData[] = {
		{ "Category", "Local Multiplayer" },
		{ "ClampMax", "4" },
		{ "ClampMin", "1" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Determines how many local players should be spawned on game start */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/SideScrollingGameMode.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Determines how many local players should be spawned on game start" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingGameMode constinit property declarations *******************
	static const UECodeGen_Private::FClassPropertyParams NewProp_UserInterfaceClass;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_UserInterface;
	static const UECodeGen_Private::FIntPropertyParams NewProp_PickupsCollected;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumberOfLocalPlayers;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingGameMode constinit property declarations *********************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingGameMode Property Definitions ******************************
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_UserInterfaceClass = { "UserInterfaceClass", nullptr, (EPropertyFlags)0x0024080000000001, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingGameMode, UserInterfaceClass), Z_Construct_UClass_UClass, Z_Construct_UClass_USideScrollingUI, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserInterfaceClass_MetaData), NewProp_UserInterfaceClass_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_UserInterface = { "UserInterface", nullptr, (EPropertyFlags)0x012408000008001c, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingGameMode, UserInterface), Z_Construct_UClass_USideScrollingUI, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UserInterface_MetaData), NewProp_UserInterface_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_PickupsCollected = { "PickupsCollected", nullptr, (EPropertyFlags)0x0020080000000014, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingGameMode, PickupsCollected), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PickupsCollected_MetaData), NewProp_PickupsCollected_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_NumberOfLocalPlayers = { "NumberOfLocalPlayers", nullptr, (EPropertyFlags)0x0020080000010001, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingGameMode, NumberOfLocalPlayers), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NumberOfLocalPlayers_MetaData), NewProp_NumberOfLocalPlayers_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UserInterfaceClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_UserInterface,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PickupsCollected,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_NumberOfLocalPlayers,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingGameMode Property Definitions ********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AGameModeBase,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingGameMode,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x008002ADu,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingGameMode;
UClass* Z_Construct_UClass_ASideScrollingGameMode(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingGameMode;
		if (!Z_Registration_Info_UClass_ASideScrollingGameMode.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingGameMode"),
				Z_Registration_Info_UClass_ASideScrollingGameMode.InnerSingleton,
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
		return Z_Registration_Info_UClass_ASideScrollingGameMode.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingGameMode.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingGameMode.OuterSingleton;
}
#undef UHT_STATICS
ASideScrollingGameMode::ASideScrollingGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingGameMode);
ASideScrollingGameMode::~ASideScrollingGameMode() {}
// ********** End Class ASideScrollingGameMode *****************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingGameMode_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingGameMode, TEXT("ASideScrollingGameMode"), &Z_Registration_Info_UClass_ASideScrollingGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingGameMode), 1653815598U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_SideScrollingGameMode_h__Script_DemoGame_dc8305e2ecdbe37c07d8a118f499c7adf9d914b8{
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
