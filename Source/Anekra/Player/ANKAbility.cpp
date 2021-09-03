#include "ANKAbility.h"

#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Game/ANKGameInstance.h"

UANKAbility::UANKAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

UEffectAsset* UANKAbility::GetEffects()
{
    return Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetEffectAsset();
}

AHero* UANKAbility::GetHero() const
{
    return Cast<AHero>(GetAvatarActorFromActorInfo());
}

AANKPlayerState* UANKAbility::GetANKPlayerState() const
{
    return Cast<AANKPlayerState>(GetHero()->GetPlayerState());
}

AANKPlayerController* UANKAbility::GetANKPlayerController() const
{
    return Cast<AANKPlayerController>(GetHero()->GetController());
}

UANKGameInstance* UANKAbility::GetANKGameInstance() const
{
    return Cast<UANKGameInstance>(GetWorld()->GetGameInstance());
}

UANKAbilitySystemComponent* UANKAbility::GetAbilitySystemComponent()
{
    return Cast<UANKAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}