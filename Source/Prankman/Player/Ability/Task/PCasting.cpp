#include "PCasting.h"

#include "Prankman/log.h"
#include "Prankman/Player/PPlayerController.h"
#include "Prankman/Player/PPlayerState.h"

UPCasting::UPCasting()
{
    //bStopWhenAbilityEnds = true;
}

void UPCasting::Activate()
{

    GetWorld()->GetTimerManager().SetTimer(CastingTimer, this, &UPCasting::OnEndCasting, 1, false, Duration);
    SetWaitingOnRemotePlayerData();

    auto PPlayerController = Cast<APPlayerController>(GetAvatarActor()->GetOwner());
    check(PPlayerController);
    PPlayerController->OnCastingDelegate.Broadcast(Duration);
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
    OwningAbility->AbilityTags.AddTag(FGameplayTag::RequestGameplayTag("State.Casting"));
    return Task;
}