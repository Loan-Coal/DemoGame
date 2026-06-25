// File: NpcGreyboxActor.h
// Module: Game
// Purpose: Concrete, spawnable NPC with a cube body + floating name label for greybox testing.
// Net I/O: no

#pragma once

#include "CoreMinimal.h"
#include "NpcActorBase.h"
#include "NpcGreyboxActor.generated.h"

class UStaticMeshComponent;
class UTextRenderComponent;

/**
 * Greybox NPC: a visible cube with the NPC's DisplayName floating above it.
 *
 * Concrete subclass of the abstract ANpcActorBase so UNpcSpawnerSubsystem can SpawnActor it
 * directly — no per-NPC Blueprint and no manual placement. Replaced by a MetaHuman-bodied
 * subclass in v2; identity (NpcId/DisplayName/LocationId) is set by the spawner at spawn time.
 */
UCLASS()
class DEMOGAME_API ANpcGreyboxActor : public ANpcActorBase
{
    GENERATED_BODY()

public:
    ANpcGreyboxActor();

protected:
    virtual void BeginPlay() override;

    /** Visible cube body (greybox stand-in for a character mesh). */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Greybox")
    TObjectPtr<UStaticMeshComponent> BodyMesh;

    /** Floating name label so the player can identify each NPC at a glance. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC|Greybox")
    TObjectPtr<UTextRenderComponent> NameLabel;
};
