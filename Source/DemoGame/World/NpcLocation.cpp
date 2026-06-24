// File: NpcLocation.cpp
// Module: DemoGame
// Purpose: Trigger-volume actor that notifies UNpcWorldSubsystem when the player arrives.
// Net I/O: no

#include "NpcLocation.h"
#include "NpcWorldSubsystem.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "DemoGame.h"

ANpcLocation::ANpcLocation()
{
    PrimaryActorTick.bCanEverTick = false;

    TriggerVolume = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerVolume"));
    TriggerVolume->SetSphereRadius(400.f);
    TriggerVolume->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = TriggerVolume;
}

void ANpcLocation::BeginPlay()
{
    Super::BeginPlay();

    if (LocationId == NAME_None)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("ANpcLocation '%s' has LocationId=None — set it in the editor."), *GetName());
    }

    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ANpcLocation::OnTriggerOverlap);
}

void ANpcLocation::OnTriggerOverlap(
    UPrimitiveComponent* /*OverlappedComp*/,
    AActor* OtherActor,
    UPrimitiveComponent* /*OtherComp*/,
    int32 /*OtherBodyIndex*/,
    bool /*bFromSweep*/,
    const FHitResult& /*SweepResult*/)
{
    // Only react to player pawns — ignore NPCs and projectiles.
    if (!OtherActor || !OtherActor->IsA<APawn>())
    {
        return;
    }
    const APlayerController* PC = Cast<APlayerController>(
        Cast<APawn>(OtherActor)->GetController());
    if (!PC)
    {
        return;
    }

    if (LocationId == NAME_None)
    {
        return;
    }

    UNpcWorldSubsystem* WS = GetWorld()
        ? GetWorld()->GetSubsystem<UNpcWorldSubsystem>()
        : nullptr;
    if (WS)
    {
        WS->OnPlayerArrived(LocationId, bFiresTick);
    }
}
