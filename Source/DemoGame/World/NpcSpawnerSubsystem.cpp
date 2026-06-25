// File: NpcSpawnerSubsystem.cpp
// Module: Game
// Purpose: Spawns the slice NPCs and notice boards from a C++ table at begin-play (no manual placement).
// Net I/O: no
// rules-allow-file: hardcoded_npc_id  (this IS the C++ spawn-roster data table; see DEC on UI/data-in-C++)

#include "NpcSpawnerSubsystem.h"
#include "GreyboxWorldSubsystem.h"
#include "NpcGreyboxActor.h"
#include "NoticeBoard.h"
#include "DemoGame.h"
#include "EngineUtils.h"
#include "CollisionQueryParams.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"

namespace
{
    // Vertical search range above/below the fallback Z for the ground trace.
    constexpr float GroundTraceHalfRange = 1000.f;

    // Notice-board rumor tiers (authored text mirrors HUMAN_VERIFICATION.md Phase 6).
    const TArray<int32> NoticeTierThresholds = { 0, 2, 4 };

    TArray<FText> MakeNoticeTiers()
    {
        return {
            FText::FromString(TEXT("The northern roads are quiet. No news from the garrison.")),
            FText::FromString(TEXT("Travelers have been talking about some skirmish up at the north pass. Hard to say what happened.")),
            FText::FromString(TEXT("They say the whole northern garrison was wiped out in one night — a divine punishment, some claim.")),
        };
    }
}

TArray<FNpcSpawnRecord> UNpcSpawnerSubsystem::GetRoster()
{
    // The C++ data source for slice NPCs. npc_id values are stable engine keys — never rename.
    // Offset is an intra-location spread (relative to GetLocationCenter) so NPCs stand apart
    // within their trigger region. Z is always 0 — ground Z is derived from a floor trace.
    // (OCP: replace this table with a DataAsset / seed-JSON loader in a later slice.)
    return {
        { TEXT("mira_innkeeper"), TEXT("Mira"),        TEXT("loc_tavern"),         FVector(  0.f, -100.f, 0.f) },
        { TEXT("lira_fence"),     TEXT("Lira"),        TEXT("loc_tavern"),         FVector(  0.f,  100.f, 0.f) },
        { TEXT("aldric_merchant"),TEXT("Aldric"),      TEXT("loc_market_square"),  FVector(-100.f,  -50.f, 0.f) },
        { TEXT("captain_sorn"),   TEXT("Captain Sorn"),TEXT("loc_guard_barracks"), FVector(  0.f,    0.f, 0.f) },
        { TEXT("old_henryk"),     TEXT("Old Henryk"),  TEXT("loc_market_square"),  FVector( 100.f,   50.f, 0.f) },
    };
}

void UNpcSpawnerSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    Super::OnWorldBeginPlay(InWorld);

    if (bSpawned || !InWorld.IsGameWorld())
    {
        return;
    }
    bSpawned = true;

    // Build the greybox world first so GetLocationCenter() is valid when SpawnNpc runs.
    if (UGreyboxWorldSubsystem* Greybox = InWorld.GetSubsystem<UGreyboxWorldSubsystem>())
    {
        Greybox->EnsureBuilt();
    }

    const FVector Base = ResolveSpawnBase(InWorld);

    for (const FNpcSpawnRecord& Record : GetRoster())
    {
        SpawnNpc(InWorld, Record, Base);
    }
    SpawnNoticeBoards(InWorld, Base);

    UE_LOG(LogDemoGame, Log, TEXT("NpcSpawnerSubsystem: spawned %d NPCs at base=%s"),
        GetRoster().Num(), *Base.ToString());
}

FVector UNpcSpawnerSubsystem::ResolveSpawnBase(UWorld& World) const
{
    for (TActorIterator<APlayerStart> It(&World); It; ++It)
    {
        return It->GetActorLocation();
    }
    return FVector::ZeroVector;
}

float UNpcSpawnerSubsystem::ResolveGroundZ(UWorld& World, const FVector& ProbeXY, float FallbackZ) const
{
    const FVector Start(ProbeXY.X, ProbeXY.Y, FallbackZ + GroundTraceHalfRange);
    const FVector End(ProbeXY.X, ProbeXY.Y, FallbackZ - GroundTraceHalfRange);

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(NpcGroundTrace), /*bTraceComplex*/ false);
    if (World.LineTraceSingleByChannel(Hit, Start, End, ECC_WorldStatic, Params))
    {
        return Hit.Location.Z;
    }

    UE_LOG(LogDemoGame, Warning,
        TEXT("NpcSpawnerSubsystem: ground trace miss at X=%.0f Y=%.0f; using fallback Z=%.0f"),
        ProbeXY.X, ProbeXY.Y, FallbackZ);
    return FallbackZ;
}

void UNpcSpawnerSubsystem::SpawnNpc(UWorld& World, const FNpcSpawnRecord& Record, const FVector& Base)
{
    // XY: greybox location center + intra-location spread; fall back to Base + offset.
    // Z: derived from a downward floor trace — actor root sits at the feet (cube mesh is offset
    // upward inside ANpcGreyboxActor so the pivot is at ground level, not cube centre).
    FVector SpawnXY = Base + Record.Offset;
    if (UGreyboxWorldSubsystem* Greybox = World.GetSubsystem<UGreyboxWorldSubsystem>())
    {
        SpawnXY = Greybox->GetLocationCenter(FName(*Record.LocationId)) + Record.Offset;
    }

    const float GroundZ = ResolveGroundZ(World, SpawnXY, Base.Z);
    const FVector Location(SpawnXY.X, SpawnXY.Y, GroundZ);  // root at feet
    const FTransform Transform(FRotator::ZeroRotator, Location);

    ANpcGreyboxActor* Npc = World.SpawnActorDeferred<ANpcGreyboxActor>(
        ANpcGreyboxActor::StaticClass(), Transform, nullptr, nullptr,
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
    if (!Npc)
    {
        UE_LOG(LogDemoGame, Warning, TEXT("NpcSpawnerSubsystem: failed to spawn NpcId=%s"),
            *Record.NpcId.ToString());
        return;
    }

    Npc->NpcId       = Record.NpcId;
    Npc->DisplayName = Record.DisplayName;
    Npc->LocationId  = Record.LocationId;
    Npc->FinishSpawning(Transform);
}

void UNpcSpawnerSubsystem::SpawnNoticeBoards(UWorld& World, const FVector& Base)
{
    const TArray<FText> Tiers = MakeNoticeTiers();
    const FVector Offsets[] = { FVector(300.f, -550.f, 0.f), FVector(300.f, 550.f, 0.f) };

    for (const FVector& Offset : Offsets)
    {
        // Notice-board mesh (BP-defined, pivot at base) rests directly on the traced floor.
        const FVector ProbeXY = Base + Offset;
        const float GroundZ = ResolveGroundZ(World, ProbeXY, Base.Z);
        const FTransform Transform(FRotator::ZeroRotator, FVector(ProbeXY.X, ProbeXY.Y, GroundZ));
        ANoticeBoard* Board = World.SpawnActorDeferred<ANoticeBoard>(
            ANoticeBoard::StaticClass(), Transform, nullptr, nullptr,
            ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
        if (!Board)
        {
            continue;
        }
        Board->RumorTiers = Tiers;
        Board->TierTickThresholds = NoticeTierThresholds;
        Board->FinishSpawning(Transform);
    }
}
