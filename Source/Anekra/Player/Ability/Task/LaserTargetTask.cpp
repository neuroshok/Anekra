#include "LaserTargetTask.h"

#include "AbilitySystemComponent.h"
#include "Anekra/Player/ANKAbility.h"
#include "Anekra/Player/ANKPlayerController.h"

void ULaserTargetTask::Activate()
{
    Cast<UANKAbility>(Ability)->GetANKPlayerController()->ClickDelegate.AddUObject(this, &ULaserTargetTask::OnClick);

    // server
    if (IsForRemoteClient())
    {
        AbilitySystemComponent->AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey()).AddUObject(this, &ULaserTargetTask::ServerOnConfirm);
        AbilitySystemComponent->CallReplicatedEventDelegateIfSet(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey());
        SetWaitingOnRemotePlayerData();
    }
}

void ULaserTargetTask::OnClick()
{
    if (IsPredictingClient())
    {
        AbilitySystemComponent->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
    }
    else AbilitySystemComponent->ConsumeGenericReplicatedEvent(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey());
    CompleteTask();
}


ULaserTargetTask* ULaserTargetTask::Create(UGameplayAbility* OwningAbility)
{
    ULaserTargetTask* Task = NewAbilityTask<ULaserTargetTask>(OwningAbility, NAME_None);
    return Task;
}

ULaserTargetTask* ULaserTargetTask::Create(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner)
{
    ULaserTargetTask* Task = NewTaskUninitialized<ULaserTargetTask>();
    check(Task && TaskOwner.GetInterface());
    Task->InitTask(*TaskOwner, FGameplayTasks::DefaultPriority);

    return Task;
}


// server
void ULaserTargetTask::ServerOnConfirm()
{
    CompleteTask();
}

void ULaserTargetTask::CompleteTask()
{
    OnCompleteDelegate.Broadcast();

    EndTask();
}