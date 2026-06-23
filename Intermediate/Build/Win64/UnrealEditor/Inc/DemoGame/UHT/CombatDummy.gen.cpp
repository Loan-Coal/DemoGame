// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatDummy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatDummy() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UPhysicsConstraintComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USceneComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatDummy(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatDamageable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatDummy(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ACombatDummy Function BP_OnDummyDamaged **********************************
struct CombatDummy_eventBP_OnDummyDamaged_Parms
{
	FVector Location;
	FVector Direction;
};
static FName NAME_ACombatDummy_BP_OnDummyDamaged = FName(TEXT("BP_OnDummyDamaged"));
void ACombatDummy::BP_OnDummyDamaged(FVector const& Location, FVector const& Direction)
{
	CombatDummy_eventBP_OnDummyDamaged_Parms Parms;
	Parms.Location=Location;
	Parms.Direction=Direction;
	UFunction* Func = FindFunctionChecked(NAME_ACombatDummy_BP_OnDummyDamaged);
	ProcessEvent(Func,&Parms);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Combat" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Blueprint handle to apply damage effects */" },
#endif
		{ "DisplayName", "On Dummy Damaged" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Blueprint handle to apply damage effects" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Location_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Direction_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnDummyDamaged constinit property declarations *********************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Location;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Direction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BP_OnDummyDamaged constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BP_OnDummyDamaged Property Definitions ********************************
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Location = { "Location", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDummy_eventBP_OnDummyDamaged_Parms, Location), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Location_MetaData), NewProp_Location_MetaData) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(CombatDummy_eventBP_OnDummyDamaged_Parms, Direction), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Direction_MetaData), NewProp_Direction_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Location,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Direction,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BP_OnDummyDamaged Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatDummy, nullptr, "BP_OnDummyDamaged", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<CombatDummy_eventBP_OnDummyDamaged_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08C80800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(CombatDummy_eventBP_OnDummyDamaged_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ACombatDummy Function BP_OnDummyDamaged ************************************

// ********** Begin Class ACombatDummy *************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ACombatDummy_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple invincible combat training dummy\n */" },
#endif
		{ "IncludePath", "Variant_Combat/Gameplay/CombatDummy.h" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple invincible combat training dummy" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Root component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Root component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BasePlate_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Static base plate */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Static base plate" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dummy_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Physics enabled dummy mesh */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physics enabled dummy mesh" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PhysicsConstraint_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Physics constraint holding the dummy and base plate together */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/Gameplay/CombatDummy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Physics constraint holding the dummy and base plate together" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ACombatDummy constinit property declarations *****************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_BasePlate;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Dummy;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PhysicsConstraint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ACombatDummy constinit property declarations *******************************
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatDummy_BP_OnDummyDamaged, "BP_OnDummyDamaged" }, // 4d81f51a4bd8a46b1d2c49ab18bc0f891d65de8a
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatDummy>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ACombatDummy Property Definitions ****************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, Root), Z_Construct_UClass_USceneComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_BasePlate = { "BasePlate", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, BasePlate), Z_Construct_UClass_UStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BasePlate_MetaData), NewProp_BasePlate_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Dummy = { "Dummy", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, Dummy), Z_Construct_UClass_UStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dummy_MetaData), NewProp_Dummy_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_PhysicsConstraint = { "PhysicsConstraint", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatDummy, PhysicsConstraint), Z_Construct_UClass_UPhysicsConstraintComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PhysicsConstraint_MetaData), NewProp_PhysicsConstraint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_BasePlate,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Dummy,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_PhysicsConstraint,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ACombatDummy Property Definitions ******************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatDamageable, (int32)VTABLE_OFFSET(ACombatDummy, ICombatDamageable), false },  // 7a4b5a8e7c3a75940e8ea3985c2adf6d465912d0
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ACombatDummy,
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
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatDummy;
UClass* Z_Construct_UClass_ACombatDummy(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ACombatDummy;
		if (!Z_Registration_Info_UClass_ACombatDummy.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatDummy"),
				Z_Registration_Info_UClass_ACombatDummy.InnerSingleton,
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
		return Z_Registration_Info_UClass_ACombatDummy.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ACombatDummy.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatDummy.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatDummy.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ACombatDummy);
ACombatDummy::~ACombatDummy() {}
// ********** End Class ACombatDummy ***************************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatDummy, TEXT("ACombatDummy"), &Z_Registration_Info_UClass_ACombatDummy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatDummy), 4267594742U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h__Script_DemoGame_80912e1b2849d401ab0b57ec5e9295ae27494159{
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
