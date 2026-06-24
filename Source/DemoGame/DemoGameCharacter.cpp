// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoGameCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputCoreTypes.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "NpcActorBase.h"
#include "DialogueManager.h"
#include "DialogueWidgetBase.h"
#include "DemoGame.h"

ADemoGameCharacter::ADemoGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ADemoGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADemoGameCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADemoGameCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADemoGameCharacter::Look);

		// Interacting (Enhanced Input path — assign IA_Interact on the character Blueprint)
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADemoGameCharacter::OnInteractPressed);
		}
	}
	else
	{
		UE_LOG(LogDemoGame, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}

	// Zero-config fallback so interaction works before IA_Interact is authored/assigned.
	if (!InteractAction && PlayerInputComponent)
	{
		PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &ADemoGameCharacter::OnInteractPressed);
	}
}

// ── NPC interaction / dialogue ───────────────────────────────────────────────

UDialogueManagerSubsystem* ADemoGameCharacter::GetDialogueManager() const
{
	return GetWorld() ? GetWorld()->GetSubsystem<UDialogueManagerSubsystem>() : nullptr;
}

ANpcActorBase* ADemoGameCharacter::FindNearestNpc() const
{
	ANpcActorBase* Best = nullptr;
	float BestDistSq = FMath::Square(InteractRadius);
	const FVector Origin = GetActorLocation();
	for (TActorIterator<ANpcActorBase> It(GetWorld()); It; ++It)
	{
		const float DistSq = FVector::DistSquared(Origin, It->GetActorLocation());
		if (DistSq <= BestDistSq)
		{
			BestDistSq = DistSq;
			Best = *It;
		}
	}
	return Best;
}

void ADemoGameCharacter::OnInteractPressed()
{
	UDialogueManagerSubsystem* DM = GetDialogueManager();
	if (!DM)
	{
		return;
	}

	if (DM->IsInDialogue())
	{
		CloseDialogue();
		return;
	}

	if (ANpcActorBase* Npc = FindNearestNpc())
	{
		OpenDialogue(Npc);
	}
	else
	{
		UE_LOG(LogDemoGame, Verbose, TEXT("Interact: no NPC within %.0f cm."), InteractRadius);
	}
}

void ADemoGameCharacter::OpenDialogue(ANpcActorBase* Npc)
{
	UDialogueManagerSubsystem* DM = GetDialogueManager();
	if (!DM || !Npc)
	{
		return;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());

	// Create + show the widget BEFORE BeginDialogue so it is bound to the subsystem when
	// OnDialogueBegun broadcasts (the widget binds the delegates in NativeConstruct).
	if (PC && DialogueWidgetClass && !ActiveDialogueWidget)
	{
		ActiveDialogueWidget = CreateWidget<UDialogueWidgetBase>(PC, DialogueWidgetClass);
		if (ActiveDialogueWidget)
		{
			ActiveDialogueWidget->AddToViewport();
		}
	}

	// Clean up regardless of who ends the conversation.
	DM->OnDialogueEnded.AddDynamic(this, &ADemoGameCharacter::HandleDialogueEnded);

	if (PC)
	{
		FInputModeGameAndUI Mode;
		if (ActiveDialogueWidget)
		{
			Mode.SetWidgetToFocus(ActiveDialogueWidget->TakeWidget());
		}
		PC->SetInputMode(Mode);
		PC->SetShowMouseCursor(true);
	}

	DM->BeginDialogue(Npc);
}

void ADemoGameCharacter::CloseDialogue()
{
	if (UDialogueManagerSubsystem* DM = GetDialogueManager())
	{
		DM->EndDialogue();   // broadcasts OnDialogueEnded → HandleDialogueEnded does the teardown
	}
}

void ADemoGameCharacter::HandleDialogueEnded()
{
	if (UDialogueManagerSubsystem* DM = GetDialogueManager())
	{
		DM->OnDialogueEnded.RemoveDynamic(this, &ADemoGameCharacter::HandleDialogueEnded);
	}

	if (ActiveDialogueWidget)
	{
		ActiveDialogueWidget->RemoveFromParent();
		ActiveDialogueWidget = nullptr;
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->SetShowMouseCursor(false);
	}
}

void ADemoGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ADemoGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ADemoGameCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ADemoGameCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ADemoGameCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ADemoGameCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}
