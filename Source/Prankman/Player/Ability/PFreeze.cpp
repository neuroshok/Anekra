#include "PFreeze.h"

#include "AbilitySystemComponent.h"
#include "Prankman/log.h"
#include "Prankman/Game/PGameState.h"
#include "Prankman/Player/PHero.h"
#include "Prankman/Player/PPlayerState.h"

void UPFreezeAbility::ActivateAbility(const FGameplayAbilitySpecHandle GameplayAbilitySpecHandle, const FGameplayAbilityActorInfo* GameplayAbilityActorInfo,
                                      const FGameplayAbilityActivationInfo GameplayAbilityActivationInfo, const FGameplayEventData* GameplayEventData)
{
    GetAbilitySystemComponentFromActorInfo()->SetRemoveAbilityOnEnd(GameplayAbilitySpecHandle);

    Super::ActivateAbility(GameplayAbilitySpecHandle, GameplayAbilityActorInfo, GameplayAbilityActivationInfo, GameplayEventData);

    PM_LOG("activate ability freeze")
    auto Hero = Cast<APHero>(GetAvatarActorFromActorInfo());
    Hero->Jump();

    for (auto PlayerState : Cast<APGameState>(GetWorld()->GetGameState())->PlayerArray)
    {
        //Cast<APPlayerState>(PlayerState)->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(FGameplayTag::RequestGameplayTag("State.Frozen"));
    }

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}