#include "Freeze.h"

#include "AbilitySystemComponent.h"

#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerState.h"

void UFreezeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* GameplayEventData)
{
    GetAbilitySystemComponent()->SetRemoveAbilityOnEnd(Handle);

    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
            return;
        }

        auto Hero = GetHero();

        for (auto PlayerState : Cast<AANKGameState>(GetWorld()->GetGameState())->PlayerArray)
        {
            if (Hero->GetPlayerState()->GetPlayerId() == PlayerState->GetPlayerId()) continue;
            GetAbilitySystemComponent()->ApplyEffect(GetAbilitySystemComponent()->Effects->FreezeEffect);
        }

        Cast<AANKPlayerController>(Hero->GetController())->RemoveAbility(Handle);
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}