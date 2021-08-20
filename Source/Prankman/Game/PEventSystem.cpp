#include "PEventSystem.h"

#include "AbilitySystemComponent.h"
#include "PGameMode.h"
#include "PGameState.h"
#include "Prankman/log.h"
#include "Prankman/Player/PPlayerState.h"
#include "Prankman/World/PCell.h"

void UPEventSystem::Start()
{
    PM_LOG("Start Event Timer")
    GetWorld()->GetTimerManager().SetTimer(EventTimer, this, &UPEventSystem::UpdateEvent, 5, false);
}

void UPEventSystem::Stop()
{

}

void UPEventSystem::UpdateEvent()
{
    auto RandomType = FMath::RandRange(static_cast<int32>(EPEventType::None), static_cast<int32>(EPEventType::Count) - 1);
    EventType = static_cast<EPEventType>(RandomType);
    GetWorld()->GetGameState<APGameState>()->ClientStartEvent(EventType);
    PM_LOG("update event %d", (int)EventType);

    // event[i]->Start();
    // wait X sec
    ClearEvent();

    for (auto PlayerState : GetWorld()->GetGameState()->PlayerArray)
    {
        auto PPlayerState = Cast<APPlayerState>(PlayerState);

        // clear event tags
        FGameplayTagContainer Tags;
        Tags.AddTag(FGameplayTag::RequestGameplayTag("Event.Snake"));
        PPlayerState->GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(Tags);

        FGameplayEffectContextHandle EffectContext = PPlayerState->GetAbilitySystemComponent()->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        auto ApplyEffect = [PPlayerState, EffectContext](TSubclassOf<class UGameplayEffect> Effect)
        { PPlayerState->GetAbilitySystemComponent()->ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1, EffectContext); };

        switch (EventType)
        {
            case EPEventType::Snake: ApplyEffect(SnakeEffect); break;
        }

        auto EffectHandle = FActiveGameplayEffectHandle::GenerateNewHandle(PPlayerState->GetAbilitySystemComponent());
    }


}

void UPEventSystem::ClearEvent()
{
    if (EventType == EPEventType::Snake)
    {
        for (APCell* Cell : Cast<APGameMode>(GetWorld()->GetAuthGameMode())->GetCells())
        {
            Cell->SetColor({0, 0, 0});
        }
    }
}