#include "WaitTagEventTask.h"

#include "Anekra/Player/ANKPlayerState.h"

void UWaitTagEventTask::Activate()
{
    AbilitySystemComponent->RegisterGameplayTagEvent(WaitingTag).AddUObject(this, &UWaitTagEventTask::OnUpdated);
}

void UWaitTagEventTask::OnDestroy(bool bInOwnerFinished)
{
    AbilitySystemComponent->RegisterGameplayTagEvent(WaitingTag).RemoveAll(this);
    OnCompleteDelegate.Clear();
    // call in last
    Super::OnDestroy(bInOwnerFinished);
}

void UWaitTagEventTask::OnUpdated(FGameplayTag Tag, int32 Count)
{
    if (Count == 0)
    {
        EndTask();
        OnCompleteDelegate.Broadcast();
    }
}

UWaitTagEventTask* UWaitTagEventTask::Create(UGameplayAbility* OwningAbility, FGameplayTag Tag)
{
    UWaitTagEventTask* Task = NewAbilityTask<UWaitTagEventTask>(OwningAbility, NAME_None);
    Task->WaitingTag = Tag;

    return Task;
}