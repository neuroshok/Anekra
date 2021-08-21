#include "PCasting.h"

#include "Prankman/Player/PPlayerState.h"

UPCasting::UPCasting()
{
    //bStopWhenAbilityEnds = true;
}

void UPCasting::Activate()
{
    GetWorld()->GetTimerManager().SetTimer(CastingTimer, this, &UPCasting::OnEndCasting, Duration);
    SetWaitingOnRemotePlayerData();

    auto PPlayerState = Cast<APPlayerState>(GetOwnerActor());
    check(PPlayerState);
    PPlayerState->OnCastingDelegate.Broadcast(Duration);
}

void UPCasting::OnEndCasting()
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnComplete.Broadcast(FGameplayTag(), FGameplayEventData());
    }
    EndTask();
}

UPCasting* UPCasting::Create(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration)
{
    UPCasting* Task = NewAbilityTask<UPCasting>(OwningAbility, TaskInstanceName);
    Task->Duration = Duration;
    return Task;
}