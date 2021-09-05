#include "ANKAbility.h"

#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Game/ANKGameInstance.h"
#include "Anekra/Game/ANKGameState.h"

UANKAbility::UANKAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UANKAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (bAutoRemove && GetANKPlayerController()) GetANKPlayerController()->RemoveAbility(Handle);
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
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

AANKGameState* UANKAbility::GetANKGameState() const
{
    return Cast<AANKGameState>(GetWorld()->GetGameState());
}

UANKAbilitySystemComponent* UANKAbility::GetAbilitySystemComponent()
{
    return Cast<UANKAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}