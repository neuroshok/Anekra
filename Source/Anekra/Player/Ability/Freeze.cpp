#include "Freeze.h"

#include "AbilitySystemComponent.h"

#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerState.h"

UFreezeAbility::UFreezeAbility()
{
    AbilityTags.AddTag(ANKTag.Ability.Freeze);
}

void UFreezeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* GameplayEventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
            return;
        }

        auto Hero = GetHero();

        for (auto PlayerState : Cast<AANKGameState>(GetWorld()->GetGameState())->GetPlayersAlive())
        {
            if (Hero->GetPlayerState()->GetPlayerId() == PlayerState->GetPlayerId()) continue;
            PlayerState->GetAbilitySystemComponent()->ApplyEffect(GetAbilitySystemComponent()->Effects->FreezeEffect);
        }
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}