#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NpcInteractionComponent.generated.h"

class ANpcActorBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractRequested, ANpcActorBase*, Npc);

/**
 * Attached to ANpcActorBase. Exposes an interact event that the player controller
 * fires when the player presses the Interact key while in range.
 *
 * TODO(Slice1): Bind to Enhanced Input "Interact" action in the player controller.
 * The controller checks distance against the InteractionRange before calling TryInteract.
 */
UCLASS(ClassGroup = "NPC", meta = (BlueprintSpawnableComponent))
class DEMOGAME_API UNpcInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNpcInteractionComponent();

    /** Maximum distance (cm) at which interaction is allowed. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Interaction")
    float InteractionRange = 200.f;

    /**
     * Called by the player controller when the interact key is pressed and
     * this NPC is the closest interactable in range.
     */
    UFUNCTION(BlueprintCallable, Category = "NPC|Interaction")
    void TryInteract(APlayerController* InstigatingPlayer);

    /** Fires when the player successfully initiates an interaction. */
    UPROPERTY(BlueprintAssignable, Category = "NPC|Interaction")
    FOnInteractRequested OnInteractRequested;
};
