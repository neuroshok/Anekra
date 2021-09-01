#include "Ability.h"

#include "Hero.h"
#include "Anekra/Game/ANKTag.h"

UAbility::UAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

AHero* UAbility::GetHero()
{
    return Cast<AHero>(GetAvatarActorFromActorInfo());
}

ANKPlayerState* UAbility::GetANKPlayerState()
{
    return Cast<ANKPlayerState>(GetHero()->GetPlayerState());
}

ANKPlayerController* UAbility::GetANKPlayerController()
{
    return Cast<ANKPlayerController>(GetHero()->GetController());
}

UANKAbilitySystemComponent* UAbility::GetAbilitySystemComponent()
{
    return Cast<UANKAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}