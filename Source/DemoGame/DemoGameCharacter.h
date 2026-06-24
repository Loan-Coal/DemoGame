// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "DemoGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class ADemoGameCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Interact Input Action (assign IA_Interact). Falls back to the E key if unset. */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;

	/** Dialogue UMG widget to spawn on interaction — a UDialogueWidgetBase subclass (assign WBP_Dialogue). */
	UPROPERTY(EditAnywhere, Category="NPC|Dialogue")
	TSubclassOf<class UDialogueWidgetBase> DialogueWidgetClass;

	/** Maximum distance (cm) to an NPC at which interaction starts a conversation. */
	UPROPERTY(EditAnywhere, Category="NPC|Dialogue")
	float InteractRadius = 250.f;

public:

	/** Constructor */
	ADemoGameCharacter();

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// ── NPC interaction / dialogue ───────────────────────────────────────────

	/** Interact pressed: open dialogue with the nearest in-range NPC, or close the active conversation. */
	void OnInteractPressed();

	/** Closest ANpcActorBase within InteractRadius, or nullptr. */
	class ANpcActorBase* FindNearestNpc() const;

	/** Spawn + show the dialogue widget, switch to UI input, then BeginDialogue. */
	void OpenDialogue(class ANpcActorBase* Npc);

	/** End the active conversation (cleanup happens in HandleDialogueEnded). */
	void CloseDialogue();

	/** Bound to the subsystem's OnDialogueEnded — tears down the widget and restores game input. */
	UFUNCTION()
	void HandleDialogueEnded();

	/** Convenience accessor for the world's dialogue subsystem. */
	class UDialogueManagerSubsystem* GetDialogueManager() const;

private:
	/** The live dialogue widget while a conversation is open. */
	UPROPERTY()
	TObjectPtr<class UDialogueWidgetBase> ActiveDialogueWidget;

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

