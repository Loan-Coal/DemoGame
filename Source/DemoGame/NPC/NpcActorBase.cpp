#include "NpcActorBase.h"
#include "DialogueComponent.h"
#include "NpcInteractionComponent.h"
#include "Components/SphereComponent.h"
#include "DemoGame.h"

ANpcActorBase::ANpcActorBase()
{
    PrimaryActorTick.bCanEverTick = false;

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetSphereRadius(200.f);
    InteractionSphere->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = InteractionSphere;

    InteractionComponent = CreateDefaultSubobject<UNpcInteractionComponent>(TEXT("InteractionComponent"));
    DialogueComponent    = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));
}

void ANpcActorBase::BeginPlay()
{
    Super::BeginPlay();

    if (NpcId.IsNone())
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("%s: NpcId is not set! Dialogue calls will fail with 422."), *GetName());
    }
}
