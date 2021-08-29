#include "Ability.h"

#include "Anekra/Game/ANKTag.h"

UAbility::UAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UANKAbilitySystemComponent* UAbility::GetAbilitySystemComponent()
{
    return Cast<UANKAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}