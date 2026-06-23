// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DemoGamePlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class UNpcEngineRestClient;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class ADemoGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

	// ── NPC Engine smoke test ────────────────────────────────────────────────

	/**
	 * Console command (exec): tests the NPC Engine pipe.
	 * Step 1: GET /health  → logs ok/fail.
	 * Step 2 (if healthy): POST /v1/dialogue with mira_innkeeper → logs npc_response.
	 * Usage in PIE console: NpcSmokeTest
	 */
	UFUNCTION(Exec, Category = "NpcEngine|Debug")
	void NpcSmokeTest();

private:
	/** Kept alive during the smoke test to prevent GC before callbacks fire. */
	UPROPERTY()
	TObjectPtr<UNpcEngineRestClient> SmokeTestClient;

};
