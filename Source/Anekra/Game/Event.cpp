#include "Event.h"

#include "ANKGameState.h"
#include "EventSystem.h"

UEvent::UEvent()
{
    OnCompleted.BindUObject(Cast<UEventSystem>(GetOuter()), &UEventSystem::Start);
}

void UEvent::Start()
{
    GetWorld()->GetGameState<AANKGameState>()->ClientUpdateEvent(GetType(), EEventPhase::Start);
}

void UEvent::Complete()
{
    if (OnCompleted.IsBound()) OnCompleted.Execute();
}

void UEvent::Delay(float Duration, TFunction<void()> Delegate)
{
    GetWorld()->GetTimerManager().SetTimer(EventTimer, TFunction<void()>{ Delegate }, Duration, false);
}