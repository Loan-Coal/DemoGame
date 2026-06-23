#include "NpcInteractionComponent.h"
#include "NpcActorBase.h"
#include "DemoGame.h"
#include "GameFramework/PlayerController.h"

UNpcInteractionComponent::UNpcInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UNpcInteractionComponent::TryInteract(APlayerController* InstigatingPlayer)
{
    if (!InstigatingPlayer)
    {
        return;
    }

    ANpcActorBase* OwnerNpc = Cast<ANpcActorBase>(GetOwner());
    if (!OwnerNpc)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("NpcInteractionComponent: owner is not ANpcActorBase."));
        return;
    }

    // Distance check — controller forwards only in-range interact events,
    // but double-check here as a guard.
    APawn* PlayerPawn = InstigatingPlayer->GetPawn();
    if (PlayerPawn)
    {
        const float DistSq = FVector::DistSquared(
            PlayerPawn->GetActorLocation(), OwnerNpc->GetActorLocation());
        if (DistSq > FMath::Square(InteractionRange))
        {
            UE_LOG(LogDemoGame, Verbose,
                TEXT("NpcInteractionComponent: player out of range (%.0f cm)."),
                FMath::Sqrt(DistSq));
            return;
        }
    }

    UE_LOG(LogDemoGame, Log,
        TEXT("NpcInteractionComponent: interact with %s (%s)"),
        *OwnerNpc->DisplayName, *OwnerNpc->NpcId.ToString());

    OnInteractRequested.Broadcast(OwnerNpc);
}
