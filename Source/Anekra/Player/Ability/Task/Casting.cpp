#include "Casting.h"

#include "Anekra/Log.h"
#include "Anekra/Player/ANKPlayerState.h"

UCasting::UCasting()
{
}

void UCasting::Activate()
{
    auto ANKPlayerState = Cast<AANKPlayerState>(GetOwnerActor());
    ANKPlayerState->OnCastingDelegate.Broadcast(Duration);
    GetWorld()->GetTimerManager().SetTimer(CastingTimer, this, &UCasting::OnCompleted, Duration);
    AbilitySystemComponent->RegisterGameplayTagEvent(ANKTag.State.Moving).AddUObject(this, &UCasting::OnCancelled);
}

void UCasting::OnDestroy(bool bInOwnerFinished)
{
    AbilitySystemComponent->RegisterGameplayTagEvent(ANKTag.State.Moving).RemoveAll(this);
    // call in last
    Super::OnDestroy(bInOwnerFinished);
}

void UCasting::OnCancelled(FGameplayTag Tag, int32 Count)
{
    if (Count > 0)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
            OnCancelDelegate.Broadcast();
        EndTask();
    }
}

void UCasting::OnCompleted()
{
    if (ShouldBroadcastAbilityTaskDelegates())
        OnCompleteDelegate.Broadcast(FGameplayTag(), FGameplayEventData());
    EndTask();
}

UCasting* UCasting::Create(UGameplayAbility* OwningAbility, float Duration)
{
    UCasting* Task = NewAbilityTask<UCasting>(OwningAbility, NAME_None);
    Task->Duration = Duration;

    return Task;
}