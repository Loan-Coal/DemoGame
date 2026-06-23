// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingPickup.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingPickup() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USphereComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingPickup(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingPickup(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingPickup Function BeginOverlap *******************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap_Statics
struct UHT_STATICS
{
	struct SideScrollingPickup_eventBeginOverlap_Parms
	{
		AActor* OverlappedActor;
		AActor* OtherActor;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles pickup collision */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles pickup collision" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BeginOverlap constinit property declarations **************************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function BeginOverlap constinit property declarations ****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function BeginOverlap Property Definitions *************************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OverlappedActor = { "OverlappedActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingPickup_eventBeginOverlap_Parms, OverlappedActor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingPickup_eventBeginOverlap_Parms, OtherActor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OverlappedActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OtherActor,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function BeginOverlap Property Definitions ***************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingPickup, nullptr, "BeginOverlap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingPickup_eventBeginOverlap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingPickup_eventBeginOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingPickup::execBeginOverlap)
{
	P_GET_OBJECT(AActor,Z_Param_OverlappedActor);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->BeginOverlap(Z_Param_OverlappedActor,Z_Param_OtherActor);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingPickup Function BeginOverlap *********************************

// ********** Begin Class ASideScrollingPickup Function BP_OnPickedUp ******************************
static FName NAME_ASideScrollingPickup_BP_OnPickedUp = FName(TEXT("BP_OnPickedUp"));
void ASideScrollingPickup::BP_OnPickedUp()
{
	UFunction* Func = FindFunctionChecked(NAME_ASideScrollingPickup_BP_OnPickedUp);
	ProcessEvent(Func,NULL);
}
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Pickup" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Passes control to BP to play effects on pickup */" },
#endif
		{ "DisplayName", "On Picked Up" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Passes control to BP to play effects on pickup" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function BP_OnPickedUp constinit property declarations *************************
// ********** End Function BP_OnPickedUp constinit property declarations ***************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingPickup, nullptr, "BP_OnPickedUp", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x08080800, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
// ********** End Class ASideScrollingPickup Function BP_OnPickedUp ********************************

// ********** Begin Class ASideScrollingPickup *****************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingPickup_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple side scrolling game pickup\n *  Increments a counter on the GameMode\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple side scrolling game pickup\nIncrements a counter on the GameMode" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Sphere_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Pickup bounding sphere */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingPickup.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Pickup bounding sphere" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingPickup constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Sphere;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingPickup constinit property declarations ***********************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("BeginOverlap"), .Pointer = &ASideScrollingPickup::execBeginOverlap },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingPickup_BeginOverlap, "BeginOverlap" }, // 367076ebd971db313e3ccd21620230762de6ad28
		{ &Z_Construct_UFunction_ASideScrollingPickup_BP_OnPickedUp, "BP_OnPickedUp" }, // 91e6eb14bffec51ee09f7c6786d6a2bce31611eb
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingPickup>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingPickup Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Sphere = { "Sphere", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingPickup, Sphere), Z_Construct_UClass_USphereComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Sphere_MetaData), NewProp_Sphere_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Sphere,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingPickup Property Definitions **********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingPickup,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	UHT_STATICS::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	0,
	0x008000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ASideScrollingPickup_StaticRegisterNativesASideScrollingPickup()
{
	UClass* Class = ASideScrollingPickup::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingPickup;
UClass* Z_Construct_UClass_ASideScrollingPickup(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingPickup;
		if (!Z_Registration_Info_UClass_ASideScrollingPickup.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingPickup"),
				Z_Registration_Info_UClass_ASideScrollingPickup.InnerSingleton,
				ASideScrollingPickup_StaticRegisterNativesASideScrollingPickup,
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
		return Z_Registration_Info_UClass_ASideScrollingPickup.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingPickup.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingPickup.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingPickup.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingPickup);
ASideScrollingPickup::~ASideScrollingPickup() {}
// ********** End Class ASideScrollingPickup *******************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingPickup_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingPickup, TEXT("ASideScrollingPickup"), &Z_Registration_Info_UClass_ASideScrollingPickup, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingPickup), 1359885344U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingPickup_h__Script_DemoGame_085a1dbfe6edd6f32803a796bfc757c27ffdba36{
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
