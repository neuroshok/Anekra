#include "StealthAbility.h"

#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Player/Hero.h"

void UStealthAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* GameplayEventData)
{
    GetAbilitySystemComponentFromActorInfo()->SetRemoveAbilityOnEnd(Handle);

    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
            return;
        }
    }
    auto Hero = Cast<AHero>(GetAvatarActorFromActorInfo());
    GetAbilitySystemComponent()->ApplyEffect(GetAbilitySystemComponent()->Effects->StealthEffect);
    Cast<AANKPlayerState>(Hero->GetPlayerState())->SetStealth();

    Cast<AANKPlayerController>(Hero->GetController())->RemoveAbility(Handle);

    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}