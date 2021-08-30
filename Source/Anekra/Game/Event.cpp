#include "Event.h"

#include "EventSystem.h"

UEvent::UEvent()
{
    OnCompleted.BindUObject(Cast<UEventSystem>(GetOuter()), &UEventSystem::Start);
}

void UEvent::Delay(float Duration, TFunction<void()> Delegate)
{
    GetWorld()->GetTimerManager().SetTimer(EventTimer, TFunction<void()>{ Delegate }, Duration, false);
}