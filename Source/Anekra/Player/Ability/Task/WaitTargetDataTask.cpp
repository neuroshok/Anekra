#include "WaitTargetDataTask.h"

#include "AbilitySystemGlobals.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Anekra/Log.h"
#include "Anekra/Player/ANKAbility.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/Hero.h"

void UWaitTargetDataTask::Activate()
{
    Cast<UANKAbility>(Ability)->GetANKPlayerController()->ClickDelegate.AddUObject(this, &UWaitTargetDataTask::OnClick);

    // server
    if (!Ability->IsLocallyControlled())
    {
        ANK_LOG("Server Activate")
        FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
        FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

        AbilitySystemComponent->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey ).AddUObject(this, &UWaitTargetDataTask::OnTargetDataReplicatedCallback);
        AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey );

        SetWaitingOnRemotePlayerData();
        ANK_LOG("Server Wait")
    }
    else ANK_LOG("Client Activate")
}

void UWaitTargetDataTask::OnClick()
{
    if (IsPredictingClient())
    {
        ANK_LOG("Client Prediction")
        /*
        FGameplayAbilityTargetingLocationInfo LocationInfo;
        LocationInfo.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
        auto DataHandle = LocationInfo.MakeTargetDataHandleFromHitResult(Ability, Result);
        UAbilitySystemGlobals::Get().InitGlobalData();
        AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag{}, AbilitySystemComponent->ScopedPredictionKey);
*/

        AbilitySystemComponent->ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::GenericConfirm, GetAbilitySpecHandle(), GetActivationPredictionKey(), AbilitySystemComponent->ScopedPredictionKey);
    }

    CompleteTask();
}


UWaitTargetDataTask* UWaitTargetDataTask::Create(UGameplayAbility* OwningAbility)
{
    UWaitTargetDataTask* Task = NewAbilityTask<UWaitTargetDataTask>(OwningAbility, NAME_None);
    return Task;
}

UWaitTargetDataTask* UWaitTargetDataTask::Create(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner)
{
    UWaitTargetDataTask* Task = NewTaskUninitialized<UWaitTargetDataTask>();
    check(Task && TaskOwner.GetInterface());
    Task->InitTask(*TaskOwner, FGameplayTasks::DefaultPriority);

    return Task;
}

FHitResult UWaitTargetDataTask::ComputeTargetLocation()
{
    auto Hero = Cast<AHero>(GetAvatarActor());
    auto SourceLocation = Hero->GetCamera()->GetComponentLocation();
    auto AimLocation = Hero->GetCamera()->GetForwardVector();
    AimLocation = SourceLocation + (AimLocation + FVector{0, 0, 0.3f}) * 5000;

    FHitResult Result;
    FCollisionObjectQueryParams ObjectParams;
    ObjectParams.ObjectTypesToQuery = FCollisionObjectQueryParams::AllDynamicObjects;
    FCollisionQueryParams Params;
    Params.TraceTag = "trace";
    GetWorld()->DebugDrawTraceTag = "trace";
    GetWorld()->LineTraceSingleByObjectType(Result, SourceLocation, AimLocation, ObjectParams, Params);
    return Result;
}

// server
void UWaitTargetDataTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag)
{
    CompleteTask();
}

void UWaitTargetDataTask::CompleteTask()
{
    ANK_LOG("Complete Task")
    auto Result = ComputeTargetLocation();
    OnCompleteDelegate.Broadcast(Result.Location);
    EndTask();
}