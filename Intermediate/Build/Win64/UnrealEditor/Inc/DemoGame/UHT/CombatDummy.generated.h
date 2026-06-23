// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Variant_Combat/Gameplay/CombatDummy.h"

#ifdef DEMOGAME_CombatDummy_generated_h
#error "CombatDummy.generated.h already included, missing '#pragma once' in CombatDummy.h"
#endif
#define DEMOGAME_CombatDummy_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ACombatDummy *************************************************************
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_19_CALLBACK_WRAPPERS
struct Z_Construct_UClass_ACombatDummy_Statics;
DEMOGAME_API UClass* Z_Construct_UClass_ACombatDummy(ETypeConstructPhase);

#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_19_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ACombatDummy_Statics; \
	friend DEMOGAME_API UClass* ::Z_Construct_UClass_ACombatDummy(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ACombatDummy, AActor, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoGame"), Z_Construct_UClass_ACombatDummy) \
	DECLARE_SERIALIZER(ACombatDummy) \
	[[deprecated("Do not call _getUObject(), use Cast.")]] virtual UObject* _getUObject() const override { return const_cast<ACombatDummy*>(this); }


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_19_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ACombatDummy(ACombatDummy&&) = delete; \
	ACombatDummy(const ACombatDummy&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ACombatDummy); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ACombatDummy); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ACombatDummy) \
	NO_API virtual ~ACombatDummy();


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_16_PROLOG
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_19_CALLBACK_WRAPPERS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_19_INCLASS_NO_PURE_DECLS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ACombatDummy;

// ********** End Class ACombatDummy ***************************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_Variant_Combat_Gameplay_CombatDummy_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
