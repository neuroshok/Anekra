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
    AbilitySystemComponent->RegisterGameplayTagEvent(ANKTag.Ability.Unlock).AddUObject(this, &UCasting::OnUpdated);
    ActivateTime = GetWorld()->GetTimeSeconds();
}

void UCasting::OnDestroy(bool bInOwnerFinished)
{
    AbilitySystemComponent->RegisterGameplayTagEvent(ANKTag.Ability.Unlock).RemoveAll(this);
    // call in last
    Super::OnDestroy(bInOwnerFinished);
}

void UCasting::OnUpdated(FGameplayTag Tag, int32 Count)
{
    if (Count == 0)
    {
        float Elapsed = GetWorld()->GetTimeSeconds() - ActivateTime;
        // cast completed
        float CastingCompleteDelta = Duration - Elapsed;
        ANK_LOG("Casting delta %f", CastingCompleteDelta)
        if (FMath::IsNearlyZero(CastingCompleteDelta, 0.01f) || CastingCompleteDelta < 0.f)
        {
            if (ShouldBroadcastAbilityTaskDelegates())
                OnCompleteDelegate.Broadcast(FGameplayTag(), FGameplayEventData());
        }
        else
        {
            if (ShouldBroadcastAbilityTaskDelegates())
                OnCancelDelegate.Broadcast();
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