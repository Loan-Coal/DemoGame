// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatDamageableBox.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatDamageableBox() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatDamageableBox(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatDamageable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatDamageableBox(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ACombatDamageableBox Function OnBoxDamaged *******************************
struct CombatDamageableBox_eventOnBoxDamaged_Parms
{
	FVector DamageLocation;
	FVector DamageImpulse;
};
static FName NAME_ACombatDamageableBox_OnBoxDamaged = FName(TEXT("OnBoxDamaged"));
void ACombatDamageableBox::OnBoxDamaged(FVector const& DamageLocation, FVector const& DamageImpulse)
{
	CombatDamageableBox_eventOnBoxDamaged_Parms Parms;
	Parms.DamageLocation=DamageLocation;
	Parms.DamageImpulse=DamageImpulse;
	UFunction* Func = FindFunctionChecked(NAME_ACombatDamageableBox_OnBoxDamaged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint damage handler for effect playback */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint damage handler for effect playback" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageLocation_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DamageImpulse_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnBoxDamaged constinit property declarations **************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_DamageLocation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_DamageImpulse;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnBoxDamaged constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnBoxDamaged Property Definitions *************************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_DamageLocation = { "DamageLocation", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDamageableBox_eventOnBoxDamaged_Parms, DamageLocation), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageLocation_MetaData), NewProp_DamageLocation_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_DamageImpulse = { "DamageImpulse", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDamageableBox_eventOnBoxDamaged_Parms, DamageImpulse), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DamageImpulse_MetaData), NewProp_DamageImpulse_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DamageLocation,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DamageImpulse,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function OnBoxDamaged Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatDamageableBox, nullptr, "OnBoxDamaged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<CombatDamageableBox_eventOnBoxDamaged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(CombatDamageableBox_eventOnBoxDamaged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ACombatDamageableBox Function OnBoxDamaged *********************************

// ********** Begin Class ACombatDamageableBox Function OnBoxDestroyed *****************************
static FName NAME_ACombatDamageableBox_OnBoxDestroyed = FName(TEXT("OnBoxDestroyed"));
void ACombatDamageableBox::OnBoxDestroyed()
{
	UFunction* Func = FindFunctionChecked(NAME_ACombatDamageableBox_OnBoxDestroyed);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint destruction handler for effect playback */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint destruction handler for effect playback" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnBoxDestroyed constinit property declarations ************************
// ********** End Function OnBoxDestroyed constinit property declarations **************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatDamageableBox, nullptr, "OnBoxDestroyed", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ACombatDamageableBox Function OnBoxDestroyed *******************************

// ********** Begin Class ACombatDamageableBox *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ACombatDamageableBox_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple physics box that reacts to damage through the ICombatDamageable interface\n */" },
#endif
		{ "IncludePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple physics box that reacts to damage through the ICombatDamageable interface" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Damageable box mesh */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Damageable box mesh" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentHP_MetaData[] = {
		{ "Category", "Damage" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Amount of HP this box starts with. */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Amount of HP this box starts with." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeathDelayTime_MetaData[] = {
		{ "Category", "Damage" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before we remove this box from the level. */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDamageableBox.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before we remove this box from the level." },
#endif
		{ "Units", "s" },
	};
#endif // WITH_METADATA

// ********** Begin Class ACombatDamageableBox constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurrentHP;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeathDelayTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ACombatDamageableBox constinit property declarations ***********************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatDamageableBox_OnBoxDamaged, "OnBoxDamaged" }, // f43359b1d44659046e72600a6381199372e942bc
		{ &Z_Construct_UFunction_ACombatDamageableBox_OnBoxDestroyed, "OnBoxDestroyed" }, // 19b138af56df0c15aa11fc7f86f5418562792fd0
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatDamageableBox>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ACombatDamageableBox Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDamageableBox, Mesh), Z_Construct_UClass_UStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_CurrentHP = { "CurrentHP", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDamageableBox, CurrentHP), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentHP_MetaData), NewProp_CurrentHP_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeathDelayTime = { "DeathDelayTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDamageableBox, DeathDelayTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeathDelayTime_MetaData), NewProp_DeathDelayTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CurrentHP,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeathDelayTime,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ACombatDamageableBox Property Definitions **********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatDamageable, (int32)VTABLE_OFFSET(ACombatDamageableBox, ICombatDamageable), false },  // 7a4b5a8e7c3a75940e8ea3985c2adf6d465912d0
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ACombatDamageableBox,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatDamageableBox;
UClass* Z_Construct_UClass_ACombatDamageableBox(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ACombatDamageableBox;
		if (!Z_Registration_Info_UClass_ACombatDamageableBox.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatDamageableBox"),
				Z_Registration_Info_UClass_ACombatDamageableBox.InnerSingleton,
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
		return Z_Registration_Info_UClass_ACombatDamageableBox.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ACombatDamageableBox.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatDamageableBox.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatDamageableBox.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ACombatDamageableBox);
ACombatDamageableBox::~ACombatDamageableBox() {}
// ********** End Class ACombatDamageableBox *******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDamageableBox_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatDamageableBox, TEXT("ACombatDamageableBox"), &Z_Registration_Info_UClass_ACombatDamageableBox, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatDamageableBox), 1108075020U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDamageableBox_h__Script_DemoGame_f5dc147377fcd6e125ce2ff09465a0d97ee95969{
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
