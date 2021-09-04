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

void UANKAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
    if (bAutoRemove) GetANKPlayerController()->RemoveAbility(Handle);
}

UEffectAsset* UANKAbility::GetEffects()
{
    return Cast<UANKGameInstance>(GetWorld()->GetGameInstance())->GetEffectAsset();
}

AHero* UANKAbility::GetHero() const
{
    check(GetAvatarActorFromActorInfo());
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