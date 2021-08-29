#include "EventSystem.h"

#include "AbilitySystemComponent.h"
#include "ANKGameInstance.h"
#include "ANKGameMode.h"
#include "ANKGameState.h"
#include "ANKTag.h"
#include "Anekra/Log.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/World/Cell.h"

void UEventSystem::Initialize()
{
    Effects = Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetEffectAsset();
}

void UEventSystem::Start()
{
    ANK_LOG("Start Event Timer")
    GetWorld()->GetTimerManager().SetTimer(EventTimer, this, &UEventSystem::UpdateEvent, 5, false);
}

void UEventSystem::Stop()
{

}

void UEventSystem::UpdateEvent()
{
    auto RandomType = FMath::RandRange(static_cast<int32>(EEventType::None), static_cast<int32>(EEventType::Count) - 1);
    EventType = static_cast<EEventType>(RandomType);
    GetWorld()->GetGameState<AANKGameState>()->ClientStartEvent(EventType);
    ANK_LOG("update event %d", (int)EventType);

    // event[i]->Start();
    // wait X sec
    ClearEvent();

    for (auto PlayerState : GetWorld()->GetGameState()->PlayerArray)
    {
        auto ANKPlayerState = Cast<AANKPlayerState>(PlayerState);

        ANKPlayerState->GetAbilitySystemComponent()->RemoveEffectByTag(ANKTag.Event.Snake);

        auto ApplyEffect = [ANKPlayerState](TSubclassOf<class UGameplayEffect> Effect)
        { ANKPlayerState->GetAbilitySystemComponent()->ApplyEffect(Effect); };

        switch (EventType)
        {
            case EEventType::Snake: ApplyEffect(Effects->SnakeEffect); break;
        }
    }
}

void UEventSystem::ClearEvent()
{
    if (EventType == EEventType::Snake)
    {
        for (ACell* Cell : Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCells())
        {
            Cell->SetColor({0, 0, 0});
        }
    }
}