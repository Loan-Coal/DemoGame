// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeDemoGame_init() {}
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
	DEMOGAME_API UFunction* Z_Construct_UDelegateFunction_DemoGame_OnEnemyDied__DelegateSignature(ETypeConstructPhase);
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_DemoGame;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_DemoGame(ETypeConstructPhase)
	{
		if (!Z_Registration_Info_UPackage__Script_DemoGame.OuterSingleton)
		{
		static FTypeConstructFunc* SingletonFuncArray[] = {
			(FTypeConstructFunc*)Z_Construct_UDelegateFunction_DemoGame_OnEnemyDied__DelegateSignature,
		};
		static const UECodeGen_Private::FPackageParams PackageParams = {
			"/Script/DemoGame",
			SingletonFuncArray,
			UE_ARRAY_COUNT(SingletonFuncArray),
			PKG_CompiledIn | 0x00000000,
			0x983E39B2,
			0xE389F30F,
			METADATA_PARAMS(0, nullptr)
		};
		UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_DemoGame.OuterSingleton, PackageParams);
	}
	return Z_Registration_Info_UPackage__Script_DemoGame.OuterSingleton;
}
static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_DemoGame(Z_Construct_UPackage__Script_DemoGame, TEXT("/Script/DemoGame"), Z_Registration_Info_UPackage__Script_DemoGame, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x983E39B2, 0xE389F30F));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
