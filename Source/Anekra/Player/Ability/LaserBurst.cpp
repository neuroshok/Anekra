#include "LaserBurst.h"

#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Anekra/Game/ANKTag.h"
#include "Anekra/Game/ANKGameState.h"
#include "Task/LaserTargetTask.h"

void ULaserBurst::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                  const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
            return;
        }

        auto Task = ULaserTargetTask::Create(this);
        Task->OnCompleteDelegate.AddUObject(this, &ULaserBurst::OnCompleted);

        Task->ReadyForActivation();
    }
}

void ULaserBurst::OnCompleted(FVector TargetLocation)
{
    for (auto Player : GetANKGameState()->GetPlayersAtCellPosition(GetANKGameState()->GetCellPosition(TargetLocation)))
    {
        auto ANKPlayer = Cast<AANKPlayerState>(Player);

        ANKPlayer->GetAbilitySystemComponent()->ApplyEffectSpec(GetAbilitySystemComponent()->Effects->DamageEffect, ANKTag.Effect.Damage, -25);
    }

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}