// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SideScrollingSoftPlatform.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeSideScrollingSoftPlatform() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UBoxComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USceneComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UStaticMeshComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingSoftPlatform(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ASideScrollingSoftPlatform(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ASideScrollingSoftPlatform Function OnSoftCollisionOverlap ***************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ASideScrollingSoftPlatform_OnSoftCollisionOverlap_Statics
struct UHT_STATICS
{
	struct SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms
	{
		UPrimitiveComponent* OverlappedComponent;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComp;
		int32 OtherBodyIndex;
		bool bFromSweep;
		FHitResult SweepResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles soft collision check box overlaps */" },
#endif
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingSoftPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles soft collision check box overlaps" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComp_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA

// ********** Begin Function OnSoftCollisionOverlap constinit property declarations ****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComp;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static void NewProp_bFromSweep_SetBit(void* Obj)
	{
		((SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms*)Obj)->bFromSweep = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SweepResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function OnSoftCollisionOverlap constinit property declarations ******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function OnSoftCollisionOverlap Property Definitions ***************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OverlappedComponent = { "OverlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms, OverlappedComponent), Z_Construct_UClass_UPrimitiveComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlappedComponent_MetaData), NewProp_OverlappedComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms, OtherActor), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_OtherComp = { "OtherComp", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms, OtherComp), Z_Construct_UClass_UPrimitiveComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComp_MetaData), NewProp_OtherComp_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms), &UHT_STATICS::NewProp_bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams UHT_STATICS::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, nullptr, nullptr, 1, STRUCT_OFFSET(SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SweepResult_MetaData), NewProp_SweepResult_MetaData) }; // e0ec7b349cc3b29366a6161006ad7fa74de2944e
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OverlappedComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OtherComp,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_OtherBodyIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bFromSweep,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SweepResult,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function OnSoftCollisionOverlap Property Definitions *****************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ASideScrollingSoftPlatform, nullptr, "OnSoftCollisionOverlap", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::SideScrollingSoftPlatform_eventOnSoftCollisionOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASideScrollingSoftPlatform_OnSoftCollisionOverlap(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ASideScrollingSoftPlatform::execOnSoftCollisionOverlap)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComp);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_GET_UBOOL(Z_Param_bFromSweep);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnSoftCollisionOverlap(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComp,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
	P_NATIVE_END;
}
// ********** End Class ASideScrollingSoftPlatform Function OnSoftCollisionOverlap *****************

// ********** Begin Class ASideScrollingSoftPlatform ***********************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ASideScrollingSoftPlatform_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A side scrolling game platform that the character can jump or drop through.\n */" },
#endif
		{ "IncludePath", "Variant_SideScrolling/Gameplay/SideScrollingSoftPlatform.h" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingSoftPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A side scrolling game platform that the character can jump or drop through." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Root_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Root component */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingSoftPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Root component" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mesh_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Platform mesh. The part we collide against and see */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingSoftPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Platform mesh. The part we collide against and see" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionCheckBox_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Collision volume that toggles soft collision on the character when they're below the platform. */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_SideScrolling/Gameplay/SideScrollingSoftPlatform.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Collision volume that toggles soft collision on the character when they're below the platform." },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ASideScrollingSoftPlatform constinit property declarations ***************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Root;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_Mesh;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollisionCheckBox;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ASideScrollingSoftPlatform constinit property declarations *****************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("OnSoftCollisionOverlap"), .Pointer = &ASideScrollingSoftPlatform::execOnSoftCollisionOverlap },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASideScrollingSoftPlatform_OnSoftCollisionOverlap, "OnSoftCollisionOverlap" }, // ecf3319978e86a3243d85de3edde82ede9fc6063
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASideScrollingSoftPlatform>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ASideScrollingSoftPlatform Property Definitions **************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Root = { "Root", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingSoftPlatform, Root), Z_Construct_UClass_USceneComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Root_MetaData), NewProp_Root_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_Mesh = { "Mesh", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingSoftPlatform, Mesh), Z_Construct_UClass_UStaticMeshComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mesh_MetaData), NewProp_Mesh_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CollisionCheckBox = { "CollisionCheckBox", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ASideScrollingSoftPlatform, CollisionCheckBox), Z_Construct_UClass_UBoxComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionCheckBox_MetaData), NewProp_CollisionCheckBox_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Root,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Mesh,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CollisionCheckBox,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ASideScrollingSoftPlatform Property Definitions ****************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ASideScrollingSoftPlatform,
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
static void ASideScrollingSoftPlatform_StaticRegisterNativesASideScrollingSoftPlatform()
{
	UClass* Class = ASideScrollingSoftPlatform::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASideScrollingSoftPlatform;
UClass* Z_Construct_UClass_ASideScrollingSoftPlatform(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ASideScrollingSoftPlatform;
		if (!Z_Registration_Info_UClass_ASideScrollingSoftPlatform.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("SideScrollingSoftPlatform"),
				Z_Registration_Info_UClass_ASideScrollingSoftPlatform.InnerSingleton,
				ASideScrollingSoftPlatform_StaticRegisterNativesASideScrollingSoftPlatform,
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
		return Z_Registration_Info_UClass_ASideScrollingSoftPlatform.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ASideScrollingSoftPlatform.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASideScrollingSoftPlatform.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ASideScrollingSoftPlatform.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ASideScrollingSoftPlatform);
ASideScrollingSoftPlatform::~ASideScrollingSoftPlatform() {}
// ********** End Class ASideScrollingSoftPlatform *************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingSoftPlatform_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASideScrollingSoftPlatform, TEXT("ASideScrollingSoftPlatform"), &Z_Registration_Info_UClass_ASideScrollingSoftPlatform, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASideScrollingSoftPlatform), 1662195344U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_SideScrolling_Gameplay_SideScrollingSoftPlatform_h__Script_DemoGame_d19788488358871112a38cea922be956a3c72e2f{
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
