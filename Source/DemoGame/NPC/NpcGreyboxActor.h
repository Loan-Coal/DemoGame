// File: NpcGreyboxActor.h
// Module: Game
// Purpose: Concrete, spawnable NPC with a cube body + floating name label for greybox testing.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "NpcActorBase.h"
#include "Engine/StreamableManager.h"
#include "NpcGreyboxActor.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;
class AActor;

/**
 * Greybox NPC: a visible cube with the NPC's DisplayName floating above it.
 *
 * Concrete subclass of the abstract ANpcActorBase so UNpcSpawnerSubsystem can SpawnActor it
 * directly — no per-NPC Blueprint and no manual placement. Replaced by a MetaHuman-bodied
 * subclass in v2; identity (NpcId/DisplayName/LocationId) is set by the spawner at spawn time.
 *
 * Avatar loading is async (DEC-042, ISSUE-017 fix): the cube stays visible until the load
 * completes; the actor can be destroyed mid-load without crashing.
 */
UCLASS()
class DEMOGAME_API ANpcGreyboxActor : public ANpcActorBase
{
    GENERATED_BODY()

public:
    ANpcGreyboxActor();

    /**
     * Optional avatar Blueprint class. When non-empty, BeginPlay requests an async asset load;
     * on completion the avatar spawns as a child actor at the actor root (feet) and the cube
     * body is hidden. NameLabel stays visible so the NPC remains identifiable above the avatar.
     * Filled by UNpcSpawnerSubsystem from NpcAppearance::GetAvatarClass — empty = keep cube.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC|Appearance")
    TSoftClassPtr<AActor> AvatarClass;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
    virtual void BeginPlay() override;

    /** Visible cube body (greybox stand-in for a character mesh). */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Greybox")
    TObjectPtr<UStaticMeshComponent> BodyMesh;

    /** Floating name label so the player can identify each NPC at a glance. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Greybox")
    TObjectPtr<UTextRenderComponent> NameLabel;

private:
    /** Requests async load of AvatarClass; cube stays visible until OnAvatarLoaded fires. */
    void BeginAsyncAvatarLoad();

    /** Fires on the game thread when the async load completes. Spawns avatar, hides cube. */
    void OnAvatarLoaded();

    /** Handle for the in-flight async load. Released in EndPlay to prevent dangling callbacks. */
    TSharedPtr<FStreamableHandle> AvatarStreamableHandle;
};
