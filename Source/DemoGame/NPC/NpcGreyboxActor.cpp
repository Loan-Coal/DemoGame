// File: NpcGreyboxActor.cpp
// Module: Game
// Purpose: Concrete, spawnable NPC with a cube body + floating name label for greybox testing.
// Net I/O: no

#include "NpcGreyboxActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "DemoGame.h"

namespace NpcGreybox
{
    // Engine primitive cube — trivial dev asset; acceptable hard ref for a greybox stand-in.
    static const TCHAR* CubeMeshPath = TEXT("/Engine/BasicShapes/Cube.Cube");

    // Half-height of the 100 cm engine cube. The actor root is placed at feet (ground level);
    // the mesh is offset up by this amount so the cube's bottom face rests on the floor.
    static constexpr float CubeHalfHeight = 50.f;

    static constexpr float LabelHeight    = 140.f;  // above the cube top face
    static constexpr float LabelWorldSize =  48.f;
}

ANpcGreyboxActor::ANpcGreyboxActor()
{
    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootComponent);
    // Offset mesh up so the actor root sits at the feet — prep for the Phase 7 avatar swap.
    BodyMesh->SetRelativeLocation(FVector(0.f, 0.f, NpcGreybox::CubeHalfHeight));
    BodyMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BodyMesh->SetCollisionResponseToAllChannels(ECR_Block);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeFinder(NpcGreybox::CubeMeshPath);
    if (CubeFinder.Succeeded())
    {
        BodyMesh->SetStaticMesh(CubeFinder.Object);
    }

    NameLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("NameLabel"));
    NameLabel->SetupAttachment(RootComponent);
    NameLabel->SetRelativeLocation(FVector(0.f, 0.f, NpcGreybox::LabelHeight));
    NameLabel->SetHorizontalAlignment(EHTA_Center);
    NameLabel->SetWorldSize(NpcGreybox::LabelWorldSize);
    NameLabel->SetTextRenderColor(FColor::White);
}

void ANpcGreyboxActor::BeginPlay()
{
    Super::BeginPlay();

    const FString Label = DisplayName.IsEmpty() ? NpcId.ToString() : DisplayName;
    NameLabel->SetText(FText::FromString(Label));

    if (!AvatarClass.IsNull())
    {
        TrySpawnAvatar();
    }
}

void ANpcGreyboxActor::TrySpawnAvatar()
{
    UClass* LoadedClass = AvatarClass.LoadSynchronous();
    if (!LoadedClass)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("NpcGreyboxActor: failed to load AvatarClass for NpcId=%s"), *NpcId.ToString());
        return;
    }

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AActor* Avatar = GetWorld()->SpawnActor<AActor>(LoadedClass, FTransform::Identity, Params);
    if (!Avatar)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("NpcGreyboxActor: SpawnActor failed for NpcId=%s"), *NpcId.ToString());
        return;
    }

    Avatar->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    BodyMesh->SetVisibility(false, /*bPropagateToChildren*/ true);
    NameLabel->SetVisibility(false);

    UE_LOG(LogDemoGame, Log,
        TEXT("NpcGreyboxActor: avatar spawned NpcId=%s Class=%s"),
        *NpcId.ToString(), *LoadedClass->GetName());
}
