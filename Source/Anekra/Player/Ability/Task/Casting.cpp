#include "Casting.h"

#include "Anekra/Log.h"
#include "Anekra/Player/ANKPlayerState.h"

UCasting::UCasting()
{
}

void UCasting::Activate()
{
    GetWorld()->GetTimerManager().SetTimer(CastingTimer, this, &UCasting::OnCompleted, Duration);

    auto ANKPlayerState = Cast<AANKPlayerState>(GetOwnerActor());
    ANKPlayerState->OnCastingDelegate.Broadcast(Duration);
    AbilitySystemComponent->RegisterGameplayTagEvent(ANKTag.Ability.Unlock).AddUObject(this, &UCasting::OnCancelled);
}

void UCasting::OnDestroy(bool bInOwnerFinished)
{
    AbilitySystemComponent->RegisterGameplayTagEvent(ANKTag.Ability.Unlock).RemoveAll(this);
    // call in last
    Super::OnDestroy(bInOwnerFinished);
}

void UCasting::OnCompleted()
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnCompleteDelegate.Broadcast(FGameplayTag(), FGameplayEventData());
    }
    EndTask();
}

void UCasting::OnCancelled(FGameplayTag Tag, int32 Count)
{
    if (Count == 0)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            OnCancelDelegate.Broadcast();
            auto ANKPlayerState = Cast<AANKPlayerState>(GetOwnerActor());
            ANKPlayerState->OnCastingCancelDelegate.Broadcast();
        }
        EndTask();
    }
}

UCasting* UCasting::Create(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration)
{
    UCasting* Task = NewAbilityTask<UCasting>(OwningAbility, TaskInstanceName);
    Task->Duration = Duration;

    return Task;
}