// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingUI.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingUI() {}

// ********** Begin Cross Module References ********************************************************
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_USideScrollingUI(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_USideScrollingUI(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class USideScrollingUI Function UpdatePickups **********************************
struct SideScrollingUI_eventUpdatePickups_Parms
{
	int32 Amount;
};
static FName NAME_USideScrollingUI_UpdatePickups = FName(TEXT("UpdatePickups"));
void USideScrollingUI::UpdatePickups(int32 Amount)
{
	SideScrollingUI_eventUpdatePickups_Parms Parms;
	Parms.Amount=Amount;
	UFunction* Func = FindFunctionChecked(NAME_USideScrollingUI_UpdatePickups);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_USideScrollingUI_UpdatePickups_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "UI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Update the widget's pickup counter */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/UI/SideScrollingUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Update the widget's pickup counter" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function UpdatePickups constinit property declarations *************************
	static const UECodeGen_Private::FIntPropertyParams NewProp_Amount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function UpdatePickups constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function UpdatePickups Property Definitions ************************************
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_Amount = { "Amount", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingUI_eventUpdatePickups_Parms, Amount), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Amount,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function UpdatePickups Property Definitions **************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_USideScrollingUI, nullptr, "UpdatePickups", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<SideScrollingUI_eventUpdatePickups_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(SideScrollingUI_eventUpdatePickups_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USideScrollingUI_UpdatePickups(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class USideScrollingUI Function UpdatePickups ************************************

// ********** Begin Class USideScrollingUI *********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_USideScrollingUI_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple Side Scrolling game UI\n *  Displays and manages a pickup counter\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/UI/SideScrollingUI.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/UI/SideScrollingUI.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple Side Scrolling game UI\nDisplays and manages a pickup counter" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class USideScrollingUI constinit property declarations *************************
// ********** End Class USideScrollingUI constinit property declarations ***************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USideScrollingUI_UpdatePickups, "UpdatePickups" }, // c97afcb2afd6859aa8c1febc532e62e33248398b
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USideScrollingUI>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_USideScrollingUI,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x00A010A1u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_USideScrollingUI;
UClass* Z_Construct_UClass_USideScrollingUI(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = USideScrollingUI;
		if (!Z_Registration_Info_UClass_USideScrollingUI.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingUI"),
				Z_Registration_Info_UClass_USideScrollingUI.InnerSingleton,
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
		return Z_Registration_Info_UClass_USideScrollingUI.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_USideScrollingUI.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USideScrollingUI.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_USideScrollingUI.OuterSingleton;
}
#undef UHT_STATICS
USideScrollingUI::USideScrollingUI(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, USideScrollingUI);
USideScrollingUI::~USideScrollingUI() {}
// ********** End Class USideScrollingUI ***********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_UI_SideScrollingUI_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USideScrollingUI, TEXT("USideScrollingUI"), &Z_Registration_Info_UClass_USideScrollingUI, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USideScrollingUI), 1219597838U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_UI_SideScrollingUI_h__Script_DemoGame_c20b8b25cffd8d456e6d99bbdc9fbf5d49dd3e91{
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
