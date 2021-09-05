#include "CrossFire.h"

#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Player/Hero.h"
#include "GameFramework/GameStateBase.h"


UCrossFireAbility::UCrossFireAbility()
{
    AbilityTags.AddTag(ANKTag.Ability.CrossFire);
}

void UCrossFireAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* GameplayEventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
            return;
        }

        auto SourcePos = GetANKPlayerState()->GetCellPosition();

        for (auto PlayerState : GetWorld()->GetGameState()->PlayerArray)
        {
            auto ANKPlayerState = Cast<AANKPlayerState>(PlayerState);
            if (PlayerState->GetPlayerId() == GetANKPlayerState()->GetPlayerId()) continue;
            auto TargetPos = ANKPlayerState->GetCellPosition();
            if (TargetPos.X == SourcePos.X || TargetPos.Y == SourcePos.Y)
                ANKPlayerState->GetAbilitySystemComponent()->ApplyEffectSpec(GetEffects()->DamageEffect, ANKTag.Effect.Damage, -20);
        }
    }

    GetAbilitySystemComponent()->PlayMontage(this, ActivationInfo, Montage, 1);

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}