// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Combat/AI/CombatEnemySpawner.h"

#ifdef DEMOGAME_CombatEnemySpawner_generated_h
#error "CombatEnemySpawner.generated.h already included, missing '#pragma once' in CombatEnemySpawner.h"
#endif
#define DEMOGAME_CombatEnemySpawner_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;

// ********** Begin Class ACombatEnemySpawner ******************************************************
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDeactivateInteraction); \
	DECLARE_FUNCTION(execActivateInteraction); \
	DECLARE_FUNCTION(execToggleInteraction); \
	DECLARE_FUNCTION(execOnEnemyDied);


struct Z_Construct_UClass_ACombatEnemySpawner_Statics;
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemySpawner(ETypeConstructPhase);

#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_23_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ACombatEnemySpawner_Statics; \
	friend DEMOGAME_API UClass* ::Z_Construct_UClass_ACombatEnemySpawner(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ACombatEnemySpawner, AActor, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoGame"), Z_Construct_UClass_ACombatEnemySpawner) \
	DECLARE_SERIALIZER(ACombatEnemySpawner) \
	[[deprecated("Do not call _getUObject(), use Cast.")]] virtual UObject* _getUObject() const override { return const_cast<ACombatEnemySpawner*>(this); }


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_23_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACombatEnemySpawner(ACombatEnemySpawner&&) = delete; \
	ACombatEnemySpawner(const ACombatEnemySpawner&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACombatEnemySpawner); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACombatEnemySpawner); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACombatEnemySpawner) \
	NO_API virtual ~ACombatEnemySpawner();


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_20_PROLOG
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_23_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_23_INCLASS_NO_PURE_DECLS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACombatEnemySpawner;

// ********** End Class ACombatEnemySpawner ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemySpawner_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
