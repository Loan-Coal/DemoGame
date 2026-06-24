#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NpcActorBase.generated.h"

class UDialogueComponent;
class UNpcInteractionComponent;
class USphereComponent;

/**
 * Base class for all NPC actors in DemoGame.
 * Carries the stable NpcId that must match the engine's seed id exactly.
 * Set NpcId in the editor for each NPC Blueprint subclass.
 *
 * Slice-1 NPCs: mira_innkeeper, lira_fence (both in loc_tavern).
 * Do NOT rename NpcId values — they are keys in the engine's Neo4j graph.
 *
 * Tomorrow: Derive a Blueprint subclass, assign the MetaHuman mesh, and place in the level.
 */
UCLASS(Abstract)
class DEMOGAME_API ANpcActorBase : public AActor
{
    GENERATED_BODY()

public:
    ANpcActorBase();

    /** Must match the engine seed id exactly e.g. "mira_innkeeper". */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Identity")
    FName NpcId;

    /** Human-readable display name shown in the dialogue UI. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Identity")
    FString DisplayName;

    /** Engine location id for this NPC's permanent location. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC|Identity")
    FString LocationId;

    /** Proximity trigger for interaction. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Components")
    TObjectPtr<USphereComponent> InteractionSphere;

    /** Handles player-initiated interact input and proximity checks. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Components")
    TObjectPtr<UNpcInteractionComponent> InteractionComponent;

    /** Owns the dialogue session with this NPC: service calls, trust, fallback. Assign DA_NpcFallbackLines in subclass defaults. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Components")
    TObjectPtr<UDialogueComponent> DialogueComponent;

protected:
    virtual void BeginPlay() override;
};
