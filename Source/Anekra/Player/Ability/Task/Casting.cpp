#include "Casting.h"

#include "Anekra/Player/ANKPlayerState.h"

UCasting::UCasting()
{
    //bStopWhenAbilityEnds = true;
}

void UCasting::Activate()
{
    GetWorld()->GetTimerManager().SetTimer(CastingTimer, this, &UCasting::OnEndCasting, Duration);
    SetWaitingOnRemotePlayerData();

    auto ANKPlayerState = Cast<AANKPlayerState>(GetOwnerActor());
    check(ANKPlayerState);
    ANKPlayerState->OnCastingDelegate.Broadcast(Duration);
}

void UCasting::OnEndCasting()
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnComplete.Broadcast(FGameplayTag(), FGameplayEventData());
    }
    EndTask();
}

UCasting* UCasting::Create(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration)
{
    UCasting* Task = NewAbilityTask<UCasting>(OwningAbility, TaskInstanceName);
    Task->Duration = Duration;
    return Task;
}