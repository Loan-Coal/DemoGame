// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatLifeBar.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatLifeBar() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor(ETypeConstructPhase);
UMG_API UClass* Z_Construct_UClass_UUserWidget(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatLifeBar(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_UCombatLifeBar(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class UCombatLifeBar Function SetBarColor **************************************
struct CombatLifeBar_eventSetBarColor_Parms
{
	FLinearColor Color;
};
static FName NAME_UCombatLifeBar_SetBarColor = FName(TEXT("SetBarColor"));
void UCombatLifeBar::SetBarColor(FLinearColor Color)
{
	CombatLifeBar_eventSetBarColor_Parms Parms;
	Parms.Color=Color;
	UFunction* Func = FindFunctionChecked(NAME_UCombatLifeBar_SetBarColor);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatLifeBar_SetBarColor_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Life Bar" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Sets the life bar fill color\n" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/UI/CombatLifeBar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the life bar fill color" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetBarColor constinit property declarations ***************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetBarColor constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetBarColor Property Definitions **************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLifeBar_eventSetBarColor_Parms, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Color,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetBarColor Property Definitions ****************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatLifeBar, nullptr, "SetBarColor", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<CombatLifeBar_eventSetBarColor_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08820800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(CombatLifeBar_eventSetBarColor_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatLifeBar_SetBarColor(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UCombatLifeBar Function SetBarColor ****************************************

// ********** Begin Class UCombatLifeBar Function SetLifePercentage ********************************
struct CombatLifeBar_eventSetLifePercentage_Parms
{
	float Percent;
};
static FName NAME_UCombatLifeBar_SetLifePercentage = FName(TEXT("SetLifePercentage"));
void UCombatLifeBar::SetLifePercentage(float Percent)
{
	CombatLifeBar_eventSetLifePercentage_Parms Parms;
	Parms.Percent=Percent;
	UFunction* Func = FindFunctionChecked(NAME_UCombatLifeBar_SetLifePercentage);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Life Bar" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Sets the life bar to the provided 0-1 percentage value*/" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/UI/CombatLifeBar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sets the life bar to the provided 0-1 percentage value" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function SetLifePercentage constinit property declarations *********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Percent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function SetLifePercentage constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function SetLifePercentage Property Definitions ********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Percent = { "Percent", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(CombatLifeBar_eventSetLifePercentage_Parms, Percent), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Percent,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function SetLifePercentage Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_UCombatLifeBar, nullptr, "SetLifePercentage", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<CombatLifeBar_eventSetLifePercentage_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08020800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(CombatLifeBar_eventSetLifePercentage_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class UCombatLifeBar Function SetLifePercentage **********************************

// ********** Begin Class UCombatLifeBar ***********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_UCombatLifeBar_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A basic life bar user widget.\n */" },
#endif
		{ "IncludePath", "Variant_Combat/UI/CombatLifeBar.h" },
		{ "ModuleRelativePath", "Variant_Combat/UI/CombatLifeBar.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic life bar user widget." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class UCombatLifeBar constinit property declarations ***************************
// ********** End Class UCombatLifeBar constinit property declarations *****************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UCombatLifeBar_SetBarColor, "SetBarColor" }, // 16a6aee1f6d53a37e8554d268da43f0a8f0fbf66
		{ &Z_Construct_UFunction_UCombatLifeBar_SetLifePercentage, "SetLifePercentage" }, // d0dd19a381936024ff134996fe907cdf9ac6f22a
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCombatLifeBar>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_UUserWidget,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_UCombatLifeBar,
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
FClassRegistrationInfo Z_Registration_Info_UClass_UCombatLifeBar;
UClass* Z_Construct_UClass_UCombatLifeBar(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = UCombatLifeBar;
		if (!Z_Registration_Info_UClass_UCombatLifeBar.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatLifeBar"),
				Z_Registration_Info_UClass_UCombatLifeBar.InnerSingleton,
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
		return Z_Registration_Info_UClass_UCombatLifeBar.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_UCombatLifeBar.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCombatLifeBar.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_UCombatLifeBar.OuterSingleton;
}
#undef UHT_STATICS
UCombatLifeBar::UCombatLifeBar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UCombatLifeBar);
UCombatLifeBar::~UCombatLifeBar() {}
// ********** End Class UCombatLifeBar *************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_UI_CombatLifeBar_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UCombatLifeBar, TEXT("UCombatLifeBar"), &Z_Registration_Info_UClass_UCombatLifeBar, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCombatLifeBar), 3225140363U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_UI_CombatLifeBar_h__Script_DemoGame_78fe49bff4c14e92d17085287ff4973cb0f419ac{
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
