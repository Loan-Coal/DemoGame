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
    static constexpr float LabelHeight = 140.f;   // above a 100cm cube
    static constexpr float LabelWorldSize = 48.f;
}

ANpcGreyboxActor::ANpcGreyboxActor()
{
    BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
    BodyMesh->SetupAttachment(RootComponent);
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
}
