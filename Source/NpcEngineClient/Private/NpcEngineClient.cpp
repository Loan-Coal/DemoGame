#include "NpcEngineClient.h"

DEFINE_LOG_CATEGORY(LogNpcEngine);

IMPLEMENT_MODULE(FNpcEngineClientModule, NpcEngineClient)

void FNpcEngineClientModule::StartupModule()
{
    UE_LOG(LogNpcEngine, Log, TEXT("NpcEngineClient module started."));
}

void FNpcEngineClientModule::ShutdownModule()
{
}
