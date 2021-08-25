#include "Freeze.h"

#include "AbilitySystemComponent.h"
#include "Anekra/Log.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerState.h"

void UFreezeAbility::ActivateAbility(const FGameplayAbilitySpecHandle GameplayAbilitySpecHandle, const FGameplayAbilityActorInfo* GameplayAbilityActorInfo,
                                      const FGameplayAbilityActivationInfo GameplayAbilityActivationInfo, const FGameplayEventData* GameplayEventData)
{
    GetAbilitySystemComponentFromActorInfo()->SetRemoveAbilityOnEnd(GameplayAbilitySpecHandle);

    Super::ActivateAbility(GameplayAbilitySpecHandle, GameplayAbilityActorInfo, GameplayAbilityActivationInfo, GameplayEventData);

    ANK_LOG("activate ability freeze")
    auto Hero = Cast<AHero>(GetAvatarActorFromActorInfo());
    Hero->Jump();

    for (auto PlayerState : Cast<AANKGameState>(GetWorld()->GetGameState())->PlayerArray)
    {
        //Cast<AANKPlayerState>(PlayerState)->GetAbilitySystemComponent()->ApplyGameplayEffectToTarget(FGameplayTag::RequestGameplayTag("State.Frozen"));
    }

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}