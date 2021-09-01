#include "Ability.h"

#include "Anekra/Game/ANKGameInstance.h"

UAbility::UAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UEffectAsset* UAbility::GetEffects()
{
    return Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetEffectAsset();
}

UMontageAsset* UAbility::GetMontages()
{
    return Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetMontageAsset();
}

AHero* UAbility::GetHero()
{
    return Cast<AHero>(GetAvatarActorFromActorInfo());
}

AANKPlayerState* UAbility::GetANKPlayerState()
{
    return Cast<AANKPlayerState>(GetHero()->GetPlayerState());
}

AANKPlayerController* UAbility::GetANKPlayerController()
{
    return Cast<AANKPlayerController>(GetHero()->GetController());
}

UANKAbilitySystemComponent* UAbility::GetAbilitySystemComponent()
{
    return Cast<UANKAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}