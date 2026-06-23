// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CombatEnemySpawner.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_UOBJECT");
void EmptyLinkFunctionForGeneratedCodeCombatEnemySpawner() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
COREUOBJECT_API UClass* Z_Construct_UClass_UClass(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_AActor(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UArrowComponent(ETypeConstructPhase);
ENGINE_API UClass* Z_Construct_UClass_UCapsuleComponent(ETypeConstructPhase);
// ********** End Cross Module References **********************************************************

// ********** Begin Same Module References *********************************************************
UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemySpawner(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ICombatActivatable(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemy(ETypeConstructPhase);
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemySpawner(ETypeConstructPhase);
// ********** End Same Module References ***********************************************************
#define UHT_STRUCT_BASE(INIT) UE::CodeGen::ConstInit::TCompiledInObjectPtr<const FStructBaseChain>(UE::Private::AsStructBaseChain(INIT))

// ********** Begin Class ACombatEnemySpawner Function ActivateInteraction *************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction_Statics
struct UHT_STATICS
{
	struct CombatEnemySpawner_eventActivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Activates the Spawner */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Activates the Spawner" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ActivateInteraction constinit property declarations *******************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ActivateInteraction constinit property declarations *********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ActivateInteraction Property Definitions ******************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemySpawner_eventActivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ActivateInteraction Property Definitions ********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatEnemySpawner, nullptr, "ActivateInteraction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatEnemySpawner_eventActivateInteraction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatEnemySpawner_eventActivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatEnemySpawner::execActivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ActivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function ActivateInteraction ***************************

// ********** Begin Class ACombatEnemySpawner Function DeactivateInteraction ***********************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction_Statics
struct UHT_STATICS
{
	struct CombatEnemySpawner_eventDeactivateInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Deactivates the Spawner */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Deactivates the Spawner" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function DeactivateInteraction constinit property declarations *****************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function DeactivateInteraction constinit property declarations *******************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function DeactivateInteraction Property Definitions ****************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemySpawner_eventDeactivateInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function DeactivateInteraction Property Definitions ******************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatEnemySpawner, nullptr, "DeactivateInteraction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatEnemySpawner_eventDeactivateInteraction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatEnemySpawner_eventDeactivateInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatEnemySpawner::execDeactivateInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->DeactivateInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function DeactivateInteraction *************************

// ********** Begin Class ACombatEnemySpawner Function OnEnemyDied *********************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Called when the spawned enemy has died */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the spawned enemy has died" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function OnEnemyDied constinit property declarations ***************************
// ********** End Function OnEnemyDied constinit property declarations *****************************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatEnemySpawner, nullptr, "OnEnemyDied", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00080401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatEnemySpawner::execOnEnemyDied)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnEnemyDied();
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function OnEnemyDied ***********************************

// ********** Begin Class ACombatEnemySpawner Function ToggleInteraction ***************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction_Statics
struct UHT_STATICS
{
	struct CombatEnemySpawner_eventToggleInteraction_Parms
	{
		AActor* ActivationInstigator;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
		{ "Category", "Activatable" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Toggles the Spawner */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Toggles the Spawner" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Function ToggleInteraction constinit property declarations *********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActivationInstigator;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Function ToggleInteraction constinit property declarations ***********************
	static const UECodeGen_Private::FFunctionParams FuncParams;
};

// ********** Begin Function ToggleInteraction Property Definitions ********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActivationInstigator = { "ActivationInstigator", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(CombatEnemySpawner_eventToggleInteraction_Parms, ActivationInstigator), Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivationInstigator,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Function ToggleInteraction Property Definitions **********************************
const UECodeGen_Private::FFunctionParams UHT_STATICS::FuncParams = { { (FTypeConstructFunc*)Z_Construct_UClass_ACombatEnemySpawner, nullptr, "ToggleInteraction", UHT_STATICS::PropPointers, UE_ARRAY_COUNT(UHT_STATICS::PropPointers), DataSizeOf<UHT_STATICS::CombatEnemySpawner_eventToggleInteraction_Parms>(), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(UHT_STATICS::Type_MetaData), UHT_STATICS::Type_MetaData)},  };
static_assert(sizeof(UHT_STATICS::CombatEnemySpawner_eventToggleInteraction_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction(ETypeConstructPhase Phase)
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, UHT_STATICS::FuncParams);
	}
	return ReturnFunction;
}
#undef UHT_STATICS
DEFINE_FUNCTION(ACombatEnemySpawner::execToggleInteraction)
{
	P_GET_OBJECT(AActor,Z_Param_ActivationInstigator);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->ToggleInteraction(Z_Param_ActivationInstigator);
	P_NATIVE_END;
}
// ********** End Class ACombatEnemySpawner Function ToggleInteraction *****************************

// ********** Begin Class ACombatEnemySpawner ******************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_Construct_UClass_ACombatEnemySpawner_Statics
struct UHT_STATICS
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Type_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n *  A basic Actor in charge of spawning Enemy Characters and monitoring their deaths.\n *  Enemies will be spawned one by one, and the spawner will wait until the enemy dies before spawning a new one.\n *  The spawner can be remotely activated through the ICombatActivatable interface\n *  When the last spawned enemy dies, the spawner can also activate other ICombatActivatables\n */" },
#endif
		{ "IncludePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A basic Actor in charge of spawning Enemy Characters and monitoring their deaths.\nEnemies will be spawned one by one, and the spawner will wait until the enemy dies before spawning a new one.\nThe spawner can be remotely activated through the ICombatActivatable interface\nWhen the last spawned enemy dies, the spawner can also activate other ICombatActivatables" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCapsule_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnDirection_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Components" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemyClass_MetaData[] = {
		{ "Category", "Enemy Spawner" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Type of enemy to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Type of enemy to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShouldSpawnEnemiesImmediately_MetaData[] = {
		{ "Category", "Enemy Spawner" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** If true, the first enemy will be spawned as soon as the game starts */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If true, the first enemy will be spawned as soon as the game starts" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialSpawnDelay_MetaData[] = {
		{ "Category", "Enemy Spawner" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before spawning the first enemy on game start */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before spawning the first enemy on game start" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCount_MetaData[] = {
		{ "Category", "Enemy Spawner" },
		{ "ClampMax", "100" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Number of enemies to spawn */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Number of enemies to spawn" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RespawnDelay_MetaData[] = {
		{ "Category", "Enemy Spawner" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait before spawning the next enemy after the current one dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait before spawning the next enemy after the current one dies" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActivationDelay_MetaData[] = {
		{ "Category", "Activation" },
		{ "ClampMax", "10" },
		{ "ClampMin", "0" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** Time to wait after this spawner is depleted before activating the actor list */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Time to wait after this spawner is depleted before activating the actor list" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ActorsToActivateWhenDepleted_MetaData[] = {
		{ "Category", "Activation" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/** List of actors to activate after the last enemy dies */" },
#endif
		{ "ModuleRelativePath", "Variant_Combat/AI/CombatEnemySpawner.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "List of actors to activate after the last enemy dies" },
#endif
	};
#endif // WITH_METADATA

// ********** Begin Class ACombatEnemySpawner constinit property declarations **********************
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnCapsule;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnDirection;
	static const UECodeGen_Private::FClassPropertyParams NewProp_EnemyClass;
	static void NewProp_bShouldSpawnEnemiesImmediately_SetBit(void* Obj)
	{
		((ACombatEnemySpawner*)Obj)->bShouldSpawnEnemiesImmediately = 1;
	}
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldSpawnEnemiesImmediately;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialSpawnDelay;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SpawnCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RespawnDelay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ActivationDelay;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ActorsToActivateWhenDepleted_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ActorsToActivateWhenDepleted;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class ACombatEnemySpawner constinit property declarations ************************
	static constexpr UE::CodeGen::FClassNativeFunction Funcs[] = {
		{ .NameUTF8 = UTF8TEXT("ActivateInteraction"), .Pointer = &ACombatEnemySpawner::execActivateInteraction },
		{ .NameUTF8 = UTF8TEXT("DeactivateInteraction"), .Pointer = &ACombatEnemySpawner::execDeactivateInteraction },
		{ .NameUTF8 = UTF8TEXT("OnEnemyDied"), .Pointer = &ACombatEnemySpawner::execOnEnemyDied },
		{ .NameUTF8 = UTF8TEXT("ToggleInteraction"), .Pointer = &ACombatEnemySpawner::execToggleInteraction },
	};
	static FTypeConstructFunc* DependentSingletons[];
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ACombatEnemySpawner_ActivateInteraction, "ActivateInteraction" }, // bfe957010c969c5ffc5bcc2f70e444704fd7981f
		{ &Z_Construct_UFunction_ACombatEnemySpawner_DeactivateInteraction, "DeactivateInteraction" }, // 639c18492cb96395d3aaa4be9eb258453ced4323
		{ &Z_Construct_UFunction_ACombatEnemySpawner_OnEnemyDied, "OnEnemyDied" }, // b2eff4e87f502b7a42c63115004e0b265d73e2be
		{ &Z_Construct_UFunction_ACombatEnemySpawner_ToggleInteraction, "ToggleInteraction" }, // 788390553e0ae8308c42bef6837859d14bf787c4
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static const UECodeGen_Private::FImplementedInterfaceParams InterfaceParams[];
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ACombatEnemySpawner>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct UHT_STATICS

// ********** Begin Class ACombatEnemySpawner Property Definitions *********************************
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SpawnCapsule = { "SpawnCapsule", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, SpawnCapsule), Z_Construct_UClass_UCapsuleComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnCapsule_MetaData), NewProp_SpawnCapsule_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_SpawnDirection = { "SpawnDirection", nullptr, (EPropertyFlags)0x00400000000a001d, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, SpawnDirection), Z_Construct_UClass_UArrowComponent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnDirection_MetaData), NewProp_SpawnDirection_MetaData) };
const UECodeGen_Private::FClassPropertyParams UHT_STATICS::NewProp_EnemyClass = { "EnemyClass", nullptr, (EPropertyFlags)0x0024080000000015, UECodeGen_Private::EPropertyGenFlags::Class, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, EnemyClass), Z_Construct_UClass_UClass, Z_Construct_UClass_ACombatEnemy, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemyClass_MetaData), NewProp_EnemyClass_MetaData) };
const UECodeGen_Private::FBoolPropertyParams UHT_STATICS::NewProp_bShouldSpawnEnemiesImmediately = { "bShouldSpawnEnemiesImmediately", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, nullptr, nullptr, 1, sizeof(bool), sizeof(ACombatEnemySpawner), &UHT_STATICS::NewProp_bShouldSpawnEnemiesImmediately_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShouldSpawnEnemiesImmediately_MetaData), NewProp_bShouldSpawnEnemiesImmediately_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_InitialSpawnDelay = { "InitialSpawnDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, InitialSpawnDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialSpawnDelay_MetaData), NewProp_InitialSpawnDelay_MetaData) };
const UECodeGen_Private::FIntPropertyParams UHT_STATICS::NewProp_SpawnCount = { "SpawnCount", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Int, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, SpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnCount_MetaData), NewProp_SpawnCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_RespawnDelay = { "RespawnDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, RespawnDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RespawnDelay_MetaData), NewProp_RespawnDelay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams UHT_STATICS::NewProp_ActivationDelay = { "ActivationDelay", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Float, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, ActivationDelay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActivationDelay_MetaData), NewProp_ActivationDelay_MetaData) };
const UECodeGen_Private::FObjectPropertyParams UHT_STATICS::NewProp_ActorsToActivateWhenDepleted_Inner = { "ActorsToActivateWhenDepleted", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, nullptr, nullptr, 1, 0, Z_Construct_UClass_AActor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams UHT_STATICS::NewProp_ActorsToActivateWhenDepleted = { "ActorsToActivateWhenDepleted", nullptr, (EPropertyFlags)0x0020080000000015, UECodeGen_Private::EPropertyGenFlags::Array, nullptr, nullptr, 1, STRUCT_OFFSET(ACombatEnemySpawner, ActorsToActivateWhenDepleted), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ActorsToActivateWhenDepleted_MetaData), NewProp_ActorsToActivateWhenDepleted_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const UHT_STATICS::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnCapsule,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnDirection,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_EnemyClass,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_bShouldSpawnEnemiesImmediately,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_InitialSpawnDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_SpawnCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_RespawnDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActivationDelay,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActorsToActivateWhenDepleted_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&UHT_STATICS::NewProp_ActorsToActivateWhenDepleted,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::PropPointers) < 2048);
// ********** End Class ACombatEnemySpawner Property Definitions ***********************************
FTypeConstructFunc* UHT_STATICS::DependentSingletons[] = {
	(FTypeConstructFunc*)Z_Construct_UClass_AActor,
	(FTypeConstructFunc*)Z_Construct_UPackage__Script_DemoGame,
};
static_assert(UE_ARRAY_COUNT(UHT_STATICS::DependentSingletons) < 16);
const UECodeGen_Private::FImplementedInterfaceParams UHT_STATICS::InterfaceParams[] = {
	{ Z_Construct_UClass_UCombatActivatable, (int32)VTABLE_OFFSET(ACombatEnemySpawner, ICombatActivatable), false },  // b1eee1007188d6f0ca67f9d59ee89eae201db24b
};
const UECodeGen_Private::FClassParams UHT_STATICS::ClassParams = {
	&Z_Construct_UClass_ACombatEnemySpawner,
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
static void ACombatEnemySpawner_StaticRegisterNativesACombatEnemySpawner()
{
	UClass* Class = ACombatEnemySpawner::StaticClass();
	FNativeFunctionRegistrar::RegisterFunctions(Class, 		MakeConstArrayView(UHT_STATICS::Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ACombatEnemySpawner;
UClass* Z_Construct_UClass_ACombatEnemySpawner(ETypeConstructPhase Phase)
{
	if (Phase == ETypeConstructPhase::Inner)
	{
		using TClass = ACombatEnemySpawner;
		if (!Z_Registration_Info_UClass_ACombatEnemySpawner.InnerSingleton)
		{
			GetPrivateStaticClassBody(
				TClass::StaticPackage(),
				TEXT("CombatEnemySpawner"),
				Z_Registration_Info_UClass_ACombatEnemySpawner.InnerSingleton,
				ACombatEnemySpawner_StaticRegisterNativesACombatEnemySpawner,
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
		return Z_Registration_Info_UClass_ACombatEnemySpawner.InnerSingleton;
	}
	if (!Z_Registration_Info_UClass_ACombatEnemySpawner.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ACombatEnemySpawner.OuterSingleton, UHT_STATICS::ClassParams);
	}
	return Z_Registration_Info_UClass_ACombatEnemySpawner.OuterSingleton;
}
#undef UHT_STATICS
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, ACombatEnemySpawner);
ACombatEnemySpawner::~ACombatEnemySpawner() {}
// ********** End Class ACombatEnemySpawner ********************************************************

// ********** Begin Registration *******************************************************************
#ifdef UHT_STATICS
#error UHT_STATICS already defined
#endif
#define UHT_STATICS Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h__Script_DemoGame_Statics
struct UHT_STATICS
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ACombatEnemySpawner, TEXT("ACombatEnemySpawner"), &Z_Registration_Info_UClass_ACombatEnemySpawner, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ACombatEnemySpawner), 1363293412U) },
	};
}; // UHT_STATICS 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h__Script_DemoGame_f79e1ce70baba7e99813c78c7078c3b42f7ce77a{
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
