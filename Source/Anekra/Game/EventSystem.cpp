#include "EventSystem.h"

#include "AbilitySystemComponent.h"
#include "ANKGameMode.h"
#include "ANKGameState.h"
#include "Anekra/Log.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/World/Cell.h"

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

        // clear event tags
        FGameplayTagContainer Tags;
        Tags.AddTag(FGameplayTag::RequestGameplayTag("Event.Snake"));
        ANKPlayerState->GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(Tags);

        FGameplayEffectContextHandle EffectContext = ANKPlayerState->GetAbilitySystemComponent()->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        auto ApplyEffect = [ANKPlayerState, EffectContext](TSubclassOf<class UGameplayEffect> Effect)
        { ANKPlayerState->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1, EffectContext); };

        switch (EventType)
        {
            case EEventType::Snake: ApplyEffect(SnakeEffect); break;
        }

        auto EffectHandle = FActiveGameplayEffectHandle::GenerateNewHandle(ANKPlayerState->GetAbilitySystemComponent());
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