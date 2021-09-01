#include "WaitTagEventTask.h"

#include "Anekra/Player/ANKPlayerState.h"

void UWaitTagEventTask::Activate()
{
    AbilitySystemComponent->RegisterGameplayTagEvent(WaitingTag).AddUObject(this, &UWaitTagEventTask::OnUpdated);
}

void UWaitTagEventTask::OnDestroy(bool bInOwnerFinished)
{
    AbilitySystemComponent->RegisterGameplayTagEvent(WaitingTag).RemoveAll(this);
    // call in last
    Super::OnDestroy(bInOwnerFinished);
}

void UWaitTagEventTask::OnUpdated(FGameplayTag Tag, int32 Count)
{
    if (Count == 0)
    {
        if (ShouldBroadcastAbilityTaskDelegates())
            OnCompleteDelegate.Broadcast();
        EndTask();
    }
}

UWaitTagEventTask* UWaitTagEventTask::Create(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayTag Tag)
{
    UWaitTagEventTask* Task = NewAbilityTask<UWaitTagEventTask>(OwningAbility, TaskInstanceName);
    Task->WaitingTag = Tag;

    return Task;
}