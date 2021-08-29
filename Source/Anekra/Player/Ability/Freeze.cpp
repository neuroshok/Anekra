#include "Freeze.h"

#include "AbilitySystemComponent.h"
#include "Anekra/Log.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerState.h"

void UFreezeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* GameplayEventData)
{
    GetAbilitySystemComponentFromActorInfo()->SetRemoveAbilityOnEnd(Handle);

    ANK_LOG("activate ability freeze")
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
            return;
        }
    }
    auto Hero = Cast<AHero>(GetAvatarActorFromActorInfo());

    for (auto PlayerState : Cast<AANKGameState>(GetWorld()->GetGameState())->PlayerArray)
    {
        if (Hero->GetPlayerState()->PlayerId == PlayerState->PlayerId) continue;
        Cast<AANKPlayerState>(PlayerState)->GetAbilitySystemComponent()->ApplyEffect(GetAbilitySystemComponent()->Effects->FrozenEffect);
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}