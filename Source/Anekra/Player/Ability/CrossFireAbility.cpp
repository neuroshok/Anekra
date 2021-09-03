#include "CrossFireAbility.h"

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
            EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
            return;
        }

        GetAbilitySystemComponentFromActorInfo()->SetRemoveAbilityOnEnd(Handle);

        auto SourcePos = GetANKPlayerState()->GetCellPosition();

        for (auto PlayerState : GetWorld()->GetGameState()->PlayerArray)
        {
            auto ANKPlayerState = Cast<AANKPlayerState>(PlayerState);
            if (PlayerState->GetPlayerId() == GetANKPlayerState()->GetPlayerId()) continue;
            auto TargetPos = ANKPlayerState->GetCellPosition();
            if (TargetPos.X == SourcePos.X || TargetPos.Y == SourcePos.Y)
                ANKPlayerState->GetAbilitySystemComponent()->ApplyEffect(GetEffects()->DamageEffect);
        }
    }



    GetAbilitySystemComponent()->PlayMontage(this, ActivationInfo, Montage, 1);

    GetANKPlayerController()->RemoveAbility(Handle);

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}