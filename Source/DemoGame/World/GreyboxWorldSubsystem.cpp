// File: GreyboxWorldSubsystem.cpp
// Module: Game
// Purpose: Procedurally builds the greybox world at begin-play: floor slab + location triggers.
// Net I/O: no

#include "GreyboxWorldSubsystem.h"
#include "NpcLocation.h"
#include "DemoGame.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/PlayerStart.h"
#include "UObject/ConstructorHelpers.h"

namespace
{
    // Engine primitive cube reused for floor slab (same asset as ANpcGreyboxActor).
    static const TCHAR* CubeMeshPath = TEXT("/Engine/BasicShapes/Cube.Cube");

    // Floor covers the full layout path (+10 % margin on each side).
    // Layout spans X: 0..3000 cm, Y: -1000..600 cm relative to WorldBase.
    constexpr float FloorLengthCm  = 4200.f;  // X extent (0..3000 + 600 margin each side)
    constexpr float FloorWidthCm   = 2000.f;  // Y extent (covers back room at -1000)
    constexpr float FloorThickCm   = 20.f;    // thin slab
    constexpr float FloorOffsetX   = 1500.f;  // center of layout along X
    constexpr float FloorOffsetY   = -200.f;  // bias toward back room
}

// -------------------------------------------------------------------------
// Layout table (single source of spatial truth for the slice)
// -------------------------------------------------------------------------

TArray<FGreyboxLocation> UGreyboxWorldSubsystem::GetLayout()
{
    // Locations spread along +X so the player walks Tavern → Market → Barracks.
    // Back room sits off the main path at negative Y (it requires a trust gate to access).
    return {
        { FName(TEXT("loc_tavern")),          FVector(   0.f,     0.f, 0.f), 500.f, true  },
        { FName(TEXT("loc_tavern_back")),     FVector(   0.f, -1000.f, 0.f), 400.f, false },
        { FName(TEXT("loc_market_square")),   FVector(1500.f,     0.f, 0.f), 500.f, true  },
        { FName(TEXT("loc_guard_barracks")),  FVector(3000.f,     0.f, 0.f), 500.f, true  },
    };
}

// -------------------------------------------------------------------------
// Subsystem lifecycle
// -------------------------------------------------------------------------

bool UGreyboxWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    const UWorld* World = Cast<UWorld>(Outer);
    return World && World->IsGameWorld();
}

void UGreyboxWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);
    EnsureBuilt();
}

// -------------------------------------------------------------------------
// Build
// -------------------------------------------------------------------------

void UGreyboxWorldSubsystem::EnsureBuilt()
{
    if (bBuilt)
    {
        return;
    }
    bBuilt = true;

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    WorldBase = ResolveWorldBase(*World);
    SpawnFloor(*World);

    for (const FGreyboxLocation& Loc : GetLayout())
    {
        SpawnLocationTrigger(*World, Loc);
    }

    UE_LOG(LogDemoGame, Log, TEXT("GreyboxWorldSubsystem: built at base=%s"), *WorldBase.ToString());
}

FVector UGreyboxWorldSubsystem::ResolveWorldBase(UWorld& World) const
{
    for (TActorIterator<APlayerStart> It(&World); It; ++It)
    {
        return It->GetActorLocation();
    }
    UE_LOG(LogDemoGame, Warning,
        TEXT("GreyboxWorldSubsystem: no PlayerStart found; using world origin"));
    return FVector::ZeroVector;
}

void UGreyboxWorldSubsystem::SpawnFloor(UWorld& World)
{
    UStaticMesh* CubeMesh = Cast<UStaticMesh>(
        StaticLoadObject(UStaticMesh::StaticClass(), nullptr, CubeMeshPath));
    if (!CubeMesh)
    {
        UE_LOG(LogDemoGame, Warning, TEXT("GreyboxWorldSubsystem: failed to load cube mesh for floor"));
        return;
    }

    // Top face of the slab aligns with WorldBase.Z so the player stands flush on it.
    const FVector FloorCenter(
        WorldBase.X + FloorOffsetX,
        WorldBase.Y + FloorOffsetY,
        WorldBase.Z - FloorThickCm * 0.5f);

    AStaticMeshActor* Floor = World.SpawnActor<AStaticMeshActor>(
        AStaticMeshActor::StaticClass(),
        FTransform(FRotator::ZeroRotator, FloorCenter));
    if (!Floor)
    {
        return;
    }

    UStaticMeshComponent* Mesh = Floor->GetStaticMeshComponent();
    Mesh->SetStaticMesh(CubeMesh);
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Mesh->SetCollisionResponseToAllChannels(ECR_Block);

    // Scale the 100 cm engine cube to cover the full layout path.
    Floor->SetActorScale3D(FVector(
        FloorLengthCm / 100.f,
        FloorWidthCm  / 100.f,
        FloorThickCm  / 100.f));
}

void UGreyboxWorldSubsystem::SpawnLocationTrigger(UWorld& World, const FGreyboxLocation& Loc)
{
    // Skip if an authored ANpcLocation with this id already exists in the level.
    for (TActorIterator<ANpcLocation> It(&World); It; ++It)
    {
        if (It->LocationId == Loc.Id)
        {
            UE_LOG(LogDemoGame, Log,
                TEXT("GreyboxWorldSubsystem: skipping %s — already placed in level"), *Loc.Id.ToString());
            return;
        }
    }

    const FVector Center = WorldBase + Loc.CenterOffset;
    ANpcLocation* Location = World.SpawnActorDeferred<ANpcLocation>(
        ANpcLocation::StaticClass(),
        FTransform(FRotator::ZeroRotator, Center),
        nullptr, nullptr,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (!Location)
    {
        UE_LOG(LogDemoGame, Warning,
            TEXT("GreyboxWorldSubsystem: failed to spawn ANpcLocation for %s"), *Loc.Id.ToString());
        return;
    }

    Location->LocationId  = Loc.Id;
    Location->bFiresTick  = Loc.bFiresTick;
    if (Location->TriggerVolume)
    {
        Location->TriggerVolume->SetSphereRadius(Loc.Radius);
    }

    Location->FinishSpawning(FTransform(FRotator::ZeroRotator, Center));
}

// -------------------------------------------------------------------------
// Accessors
// -------------------------------------------------------------------------

FVector UGreyboxWorldSubsystem::GetLocationCenter(FName LocationId) const
{
    for (const FGreyboxLocation& Loc : GetLayout())
    {
        if (Loc.Id == LocationId)
        {
            return WorldBase + Loc.CenterOffset;
        }
    }
    UE_LOG(LogDemoGame, Warning,
        TEXT("GreyboxWorldSubsystem: unknown location '%s'; falling back to WorldBase"),
        *LocationId.ToString());
    return WorldBase;
}
