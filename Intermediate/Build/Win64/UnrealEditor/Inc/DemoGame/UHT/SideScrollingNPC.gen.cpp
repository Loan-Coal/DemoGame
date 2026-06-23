// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingNPC.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingNPC() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingNPC(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ISideScrollingInteractable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingNPC(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingNPC ********************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingNPC_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  Simple platforming NPC\n *  Its behaviors will be dictated by a possessing AI Controller\n *  It can be temporarily deactivated through Actor interactions\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Simple platforming NPC\nIts behaviors will be dictated by a possessing AI Controller\nIt can be temporarily deactivated through Actor interactions" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LaunchImpulse_MetaData[] = {
		{ "Category", "NPC" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Horizontal impulse to apply to the NPC when it's interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Horizontal impulse to apply to the NPC when it's interacted with" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LaunchVerticalImpulse_MetaData[] = {
		{ "Category", "NPC" },
		{ "ClampMax", "10000" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Vertical impulse to apply to the NPC when it's interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Vertical impulse to apply to the NPC when it's interacted with" },
#endif
		{ "Units", "cm/s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DeactivationTime_MetaData[] = {
		{ "Category", "NPC" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time that the NPC remains deactivated after being interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time that the NPC remains deactivated after being interacted with" },
#endif
		{ "Units", "s" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDeactivated_MetaData[] = {
		{ "Category", "NPC" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, this NPC is deactivated and will not be interacted with */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/AI/SideScrollingNPC.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, this NPC is deactivated and will not be interacted with" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingNPC constinit property declarations ************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LaunchImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LaunchVerticalImpulse;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DeactivationTime;
	static void NewProp_bDeactivated_SetBit(void* Obj)
	{
		((ASideScrollingNPC*)Obj)->bDeactivated = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDeactivated;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingNPC constinit property declarations **************************
	static FTypeConstructFunc* DependentSingletons[];
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingNPC>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingNPC Property Definitions ***********************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LaunchImpulse = { "LaunchImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingNPC, LaunchImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LaunchImpulse_MetaData), NewProp_LaunchImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_LaunchVerticalImpulse = { "LaunchVerticalImpulse", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingNPC, LaunchVerticalImpulse), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LaunchVerticalImpulse_MetaData), NewProp_LaunchVerticalImpulse_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_DeactivationTime = { "DeactivationTime", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingNPC, DeactivationTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DeactivationTime_MetaData), NewProp_DeactivationTime_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bDeactivated = { "bDeactivated", nullptr, (EPropertyFlags)0x0010000000020015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ASideScrollingNPC), &UHT_STATICS::NewProp_bDeactivated_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDeactivated_MetaData), NewProp_bDeactivated_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LaunchImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LaunchVerticalImpulse,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_DeactivationTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bDeactivated,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingNPC Property Definitions *************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ACharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_USideScrollingInteractable, (int32)VTABLE_OFFSET(ASideScrollingNPC, ISideScrollingInteractable), false },  // 16a90723bd7e749750935d50cae1ea5a1ab3a753
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingNPC,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	UHT_STATICS::PropPointers,
	InterfaceParams,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(UHT_STATICS::PropPointers),
	UE_ARRAY_COUNT(InterfaceParams),
	0x008000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingNPC;
UClass* Z_Construct_UClass_ASideScrollingNPC(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingNPC;
		if (!Z_Registration_Info_UClass_ASideScrollingNPC.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingNPC"),
				Z_Registration_Info_UClass_ASideScrollingNPC.InnerSingleton,
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
		return Z_Registration_Info_UClass_ASideScrollingNPC.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingNPC.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingNPC.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingNPC.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingNPC);
ASideScrollingNPC::~ASideScrollingNPC() {}
// ********** End Class ASideScrollingNPC **********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_AI_SideScrollingNPC_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingNPC, TEXT("ASideScrollingNPC"), &Z_Registration_Info_UClass_ASideScrollingNPC, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingNPC), 3039979480U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_AI_SideScrollingNPC_h__Script_DemoGame_2d9bc4f97da0e4d415446843fcf071487607b361{
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
