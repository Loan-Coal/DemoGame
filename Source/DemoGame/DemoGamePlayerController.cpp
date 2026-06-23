// Copyright Epic Games, Inc. All Rights Reserved.


#include "DemoGamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "DemoGame.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "NpcEngineRestClient.h"
#include "NpcEngineTypes.h"

void ADemoGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (IsLocalPlayerController() && ShouldUseTouchControls())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogDemoGame, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void ADemoGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool ADemoGamePlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

void ADemoGamePlayerController::NpcSmokeTest()
{
	UE_LOG(LogDemoGame, Display, TEXT("=== NpcSmokeTest BEGIN ==="));

	// Create a client owned by this controller so it survives the async callbacks.
	SmokeTestClient = NewObject<UNpcEngineRestClient>(this);
	UNpcEngineRestClient* Client = SmokeTestClient;

	// Step 1: health check.
	Client->GetHealth([this, Client](bool bOk)
	{
		UE_LOG(LogDemoGame, Display,
			TEXT("NpcSmokeTest | Health: %s"), bOk ? TEXT("OK") : TEXT("FAIL - engine unreachable"));

		if (!bOk)
		{
			UE_LOG(LogDemoGame, Warning,
				TEXT("NpcSmokeTest | Skipping dialogue test — start docker-compose first."));
			UE_LOG(LogDemoGame, Display, TEXT("=== NpcSmokeTest END (health fail) ==="));
			return;
		}

		// Step 2: one dialogue turn with Mira.
		FNpcDialogueRequest Req;
		Req.PlayerId      = TEXT("player_demo");
		Req.NpcId         = TEXT("mira_innkeeper");
		Req.PlayerMessage = TEXT("Good evening, Mira.");

		FOnNpcDialogueComplete SuccessDelegate;
		SuccessDelegate.BindLambda([this](const FNpcDialogueResponse& Response)
		{
			UE_LOG(LogDemoGame, Display,
				TEXT("NpcSmokeTest | Mira says: \"%s\""), *Response.NpcResponse);
			UE_LOG(LogDemoGame, Display,
				TEXT("NpcSmokeTest | degradation_level=%s cached=%s"),
				*Response.DegradationLevel,
				Response.bCached ? TEXT("true") : TEXT("false"));
			UE_LOG(LogDemoGame, Display,
				TEXT("=== NpcSmokeTest PASS ==="));
			SmokeTestClient = nullptr;   // release reference
		});

		FOnNpcEngineError ErrorDelegate;
		ErrorDelegate.BindLambda([this](const FString& Err)
		{
			UE_LOG(LogDemoGame, Warning,
				TEXT("NpcSmokeTest | Dialogue FAIL: %s"), *Err);
			UE_LOG(LogDemoGame, Display, TEXT("=== NpcSmokeTest END (dialogue fail) ==="));
			SmokeTestClient = nullptr;
		});

		Client->SendDialogue(Req, SuccessDelegate, ErrorDelegate);
	});
}
