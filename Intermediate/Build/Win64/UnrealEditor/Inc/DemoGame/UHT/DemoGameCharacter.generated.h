// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "DemoGameCharacter.h"

#ifdef DEMOGAME_DemoGameCharacter_generated_h
#error "DemoGameCharacter.generated.h already included, missing '#pragma once' in DemoGameCharacter.h"
#endif
#define DEMOGAME_DemoGameCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ReflectedTypeAccessors.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ADemoGameCharacter *******************************************************
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execDoJumpEnd); \
	DECLARE_FUNCTION(execDoJumpStart); \
	DECLARE_FUNCTION(execDoLook); \
	DECLARE_FUNCTION(execDoMove);


struct Z_Construct_UClass_ADemoGameCharacter_Statics;
DEMOGAME_API UClass* Z_Construct_UClass_ADemoGameCharacter(ETypeConstructPhase);

#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_24_INCLASS_NO_PURE_DECLS \
private: \
	friend struct ::Z_Construct_UClass_ADemoGameCharacter_Statics; \
	friend DEMOGAME_API UClass* ::Z_Construct_UClass_ADemoGameCharacter(ETypeConstructPhase); \
public: \
	DECLARE_CLASS2(ADemoGameCharacter, ACharacter, COMPILED_IN_FLAGS(CLASS_Abstract | CLASS_Config), CASTCLASS_None, TEXT("/Script/DemoGame"), Z_Construct_UClass_ADemoGameCharacter) \
	DECLARE_SERIALIZER(ADemoGameCharacter)


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_24_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ADemoGameCharacter(ADemoGameCharacter&&) = delete; \
	ADemoGameCharacter(const ADemoGameCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ADemoGameCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ADemoGameCharacter); \
	DEFINE_ABSTRACT_DEFAULT_CONSTRUCTOR_CALL(ADemoGameCharacter) \
	NO_API virtual ~ADemoGameCharacter();


#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_21_PROLOG
#define FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_24_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_24_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_24_INCLASS_NO_PURE_DECLS \
	FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h_24_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ADemoGameCharacter;

// ********** End Class ADemoGameCharacter *********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_lohan_OneDrive_Documents_Unreal_Projects_DemoGame_Source_DemoGame_DemoGameCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
