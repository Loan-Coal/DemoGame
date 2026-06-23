// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DemoGameCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeDemoGameCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_ACharacter(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent(ETypeConstructPhase);
ENHANCEDINPUT_API UClass* Z_Construct_UClass_UInputAction(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ADemoGameCharacter(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ADemoGameCharacter(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ADemoGameCharacter Function DoJumpEnd ************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADemoGameCharacter_DoJumpEnd_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpEnd constinit property declarations *****************************
// ********** End Function DoJumpEnd constinit property declarations *******************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADemoGameCharacter, nullptr, "DoJumpEnd", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADemoGameCharacter_DoJumpEnd(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADemoGameCharacter::execDoJumpEnd)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpEnd();
	P_NATIVE_END;
}
// ********** End Class ADemoGameCharacter Function DoJumpEnd **************************************

// ********** Begin Class ADemoGameCharacter Function DoJumpStart **********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADemoGameCharacter_DoJumpStart_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles jump pressed inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles jump pressed inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoJumpStart constinit property declarations ***************************
// ********** End Function DoJumpStart constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADemoGameCharacter, nullptr, "DoJumpStart", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ADemoGameCharacter_DoJumpStart(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADemoGameCharacter::execDoJumpStart)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoJumpStart();
	P_NATIVE_END;
}
// ********** End Class ADemoGameCharacter Function DoJumpStart ************************************

// ********** Begin Class ADemoGameCharacter Function DoLook ***************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADemoGameCharacter_DoLook_Statics
struct UHT_STATICS
{
	struct DemoGameCharacter_eventDoLook_Parms
	{
		float Yaw;
		float Pitch;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles look inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles look inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoLook constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Yaw;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Pitch;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoLook constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoLook Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Yaw = { "Yaw", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DemoGameCharacter_eventDoLook_Parms, Yaw), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Pitch = { "Pitch", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DemoGameCharacter_eventDoLook_Parms, Pitch), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Yaw,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Pitch,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoLook Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADemoGameCharacter, nullptr, "DoLook", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DemoGameCharacter_eventDoLook_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DemoGameCharacter_eventDoLook_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADemoGameCharacter_DoLook(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADemoGameCharacter::execDoLook)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Yaw);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Pitch);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoLook(Z_Param_Yaw,Z_Param_Pitch);
	P_NATIVE_END;
}
// ********** End Class ADemoGameCharacter Function DoLook *****************************************

// ********** Begin Class ADemoGameCharacter Function DoMove ***************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ADemoGameCharacter_DoMove_Statics
struct UHT_STATICS
{
	struct DemoGameCharacter_eventDoMove_Parms
	{
		float Right;
		float Forward;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Handles move inputs from either controls or UI interfaces */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Handles move inputs from either controls or UI interfaces" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DoMove constinit property declarations ********************************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Right;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Forward;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DoMove constinit property declarations **********************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DoMove Property Definitions *******************************************
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Right = { "Right", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DemoGameCharacter_eventDoMove_Parms, Right), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_Forward = { "Forward", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(DemoGameCharacter_eventDoMove_Parms, Forward), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Right,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_Forward,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DoMove Property Definitions *********************************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ADemoGameCharacter, nullptr, "DoMove", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::DemoGameCharacter_eventDoMove_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::DemoGameCharacter_eventDoMove_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ADemoGameCharacter_DoMove(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ADemoGameCharacter::execDoMove)
{
	P_GET_PROPERTY(FFloatProperty,Z_Param_Right);
	P_GET_PROPERTY(FFloatProperty,Z_Param_Forward);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DoMove(Z_Param_Right,Z_Param_Forward);
	P_NATIVE_END;
}
// ********** End Class ADemoGameCharacter Function DoMove *****************************************

// ********** Begin Class ADemoGameCharacter *******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ADemoGameCharacter_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A simple player-controllable third person character\n *  Implements a controllable orbiting camera\n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "DemoGameCharacter.h" },
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A simple player-controllable third person character\nImplements a controllable orbiting camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Camera boom positioning the camera behind the character */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Camera boom positioning the camera behind the character" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FollowCamera_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Follow camera */" },
#endif
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Follow camera" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_JumpAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Jump Input Action */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Jump Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoveAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Move Input Action */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Move Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Look Input Action */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Look Input Action" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MouseLookAction_MetaData[] = {
		{ "Category", "Input" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Mouse Look Input Action */" },
#endif
		{ "ModuleRelativePath", "DemoGameCharacter.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mouse Look Input Action" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ADemoGameCharacter constinit property declarations ***********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CameraBoom;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_FollowCamera;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_JumpAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MoveAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_LookAction;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_MouseLookAction;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ADemoGameCharacter constinit property declarations *************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("DoJumpEnd"), .Pointer = &ADemoGameCharacter::execDoJumpEnd },
		{ .NameUTF8 = UTF8TEXT("DoJumpStart"), .Pointer = &ADemoGameCharacter::execDoJumpStart },
		{ .NameUTF8 = UTF8TEXT("DoLook"), .Pointer = &ADemoGameCharacter::execDoLook },
		{ .NameUTF8 = UTF8TEXT("DoMove"), .Pointer = &ADemoGameCharacter::execDoMove },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ADemoGameCharacter_DoJumpEnd, "DoJumpEnd" }, // ea8639443894fa440912a8b0aca76672e57f6f64
		{ &Z_Construct_UFunction_ADemoGameCharacter_DoJumpStart, "DoJumpStart" }, // a33fbf7966c5daf5b025b0fa168fb8c6b79d4644
		{ &Z_Construct_UFunction_ADemoGameCharacter_DoLook, "DoLook" }, // 40251824bf1a0fcb96e5a995583382eb60ac395e
		{ &Z_Construct_UFunction_ADemoGameCharacter_DoMove, "DoMove" }, // 421939995220cb31784fe1f58b585415dc0b7197
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ADemoGameCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ADemoGameCharacter Property Definitions **********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_CameraBoom = { "CameraBoom", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADemoGameCharacter, CameraBoom), Z_Construct_UClass_USpringArmComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraBoom_MetaData), NewProp_CameraBoom_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_FollowCamera = { "FollowCamera", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADemoGameCharacter, FollowCamera), Z_Construct_UClass_UCameraComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FollowCamera_MetaData), NewProp_FollowCamera_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_JumpAction = { "JumpAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADemoGameCharacter, JumpAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_JumpAction_MetaData), NewProp_JumpAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MoveAction = { "MoveAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADemoGameCharacter, MoveAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoveAction_MetaData), NewProp_MoveAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_LookAction = { "LookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADemoGameCharacter, LookAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LookAction_MetaData), NewProp_LookAction_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_MouseLookAction = { "MouseLookAction", nullptr, (EPropertyFlags)0x0020080000000001, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ADemoGameCharacter, MouseLookAction), Z_Construct_UClass_UInputAction, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MouseLookAction_MetaData), NewProp_MouseLookAction_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_FollowCamera,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_JumpAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MoveAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_LookAction,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_MouseLookAction,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ADemoGameCharacter Property Definitions ************************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_ACharacter,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ADemoGameCharacter,
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
	0x008000A5u,
	METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)
};
static void ADemoGameCharacter_StaticRegisterNativesADemoGameCharacter()
{
	UClass* Class = ADemoGameCharacter::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ADemoGameCharacter;
UClass* Z_Construct_UClass_ADemoGameCharacter(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ADemoGameCharacter;
		if (!Z_Registration_Info_UClass_ADemoGameCharacter.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("DemoGameCharacter"),
				Z_Registration_Info_UClass_ADemoGameCharacter.InnerSingleton,
				ADemoGameCharacter_StaticRegisterNativesADemoGameCharacter,
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
		return Z_Registration_Info_UClass_ADemoGameCharacter.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ADemoGameCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ADemoGameCharacter.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ADemoGameCharacter.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ADemoGameCharacter);
ADemoGameCharacter::~ADemoGameCharacter() {}
// ********** End Class ADemoGameCharacter *********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ADemoGameCharacter, TEXT("ADemoGameCharacter"), &Z_Registration_Info_UClass_ADemoGameCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ADemoGameCharacter), 831495958U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h__Script_DemoGame_3ec95852bbecf8798d2c1874850ccb6c1c6b68ea{
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
