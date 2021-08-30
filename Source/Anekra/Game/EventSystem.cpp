#include "EventSystem.h"

#include "AbilitySystemComponent.h"
#include "ANKGameInstance.h"
#include "ANKGameMode.h"
#include "ANKGameState.h"
#include "ANKTag.h"
#include "Anekra/Log.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/World/Cell.h"
#include "Event/SnakeEvent.h"

UEventSystem::UEventSystem()
{
    NoEventDuration = 5.f;
}

void UEventSystem::Initialize()
{
    Effects = Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetEffectAsset();

    Events.Add(NewObject<USnakeEvent>(this));
    //Events.Add(NewObject<UFindCellEvent>(this));
}

void UEventSystem::Start()
{
    ANK_LOG("Start Event Timer, wait %f", NoEventDuration)
    GetWorld()->GetTimerManager().SetTimer(EventTimer, this, &UEventSystem::StartEvent, NoEventDuration);
}

void UEventSystem::Stop()
{

}

void UEventSystem::StartEvent()
{
    check(Events.Num() > 0);
    auto RandomIndex = FMath::RandRange(0, Events.Num() - 1);
    Events[RandomIndex]->Start();
    ANK_LOG("Start event Index: %d", RandomIndex);
}