// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Combat/AI/CombatEnemy.h"

#ifdef DEMOGAME_CombatEnemy_generated_h
#error "CombatEnemy.generated.h already included, missing '#pragma once' in CombatEnemy.h"
#endif
#define DEMOGAME_CombatEnemy_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ACombatEnemy *************************************************************
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execCheckChargedAttack); \
	DECLARE_FUNCTION(execCheckCombo);


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ACombatEnemy_Statics;
DEMOGAME_API UClass* Z_Construct_UClass_ACombatEnemy(ETypeConstructPhase);

#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ACombatEnemy_Statics; \
	friend DEMOGAME_API UClass* ::Z_Construct_UClass_ACombatEnemy(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ACombatEnemy, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoGame"), Z_Construct_UClass_ACombatEnemy) \
	DECLARE_SERIALIZER(ACombatEnemy) \
	[[deprecated("Do not call _getUObject(), use Cast.")]] virtual UObject* _getUObject() const override { return const_cast<ACombatEnemy*>(this); }


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACombatEnemy(ACombatEnemy&&) = delete; \
	ACombatEnemy(const ACombatEnemy&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACombatEnemy); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACombatEnemy); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACombatEnemy) \
	NO_API virtual ~ACombatEnemy();


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_30_PROLOG
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_CALLBACK_WRAPPERS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_INCLASS_NO_PURE_DECLS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h_33_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACombatEnemy;

// ********** End Class ACombatEnemy ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_AI_CombatEnemy_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
