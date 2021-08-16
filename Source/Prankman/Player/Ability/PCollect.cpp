#include "PCollect.h"

#include "AbilitySystemComponent.h"
#include "Prankman/log.h"
#include "Prankman/Player/PHero.h"
#include "Task/PCasting.h"

UPCollectAbility::UPCollectAbility()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Collect")));
}

bool UPCollectAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    bool Activatable = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
    auto Hero = Cast<APHero>(GetAvatarActorFromActorInfo());
    return Activatable && Hero->GetVelocity().IsZero();
}

void UPCollectAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
            return;
        }

        auto Task = UPCasting::Create(this, NAME_None, 2);
        Task->OnComplete.AddUObject(this, &UPCollectAbility::OnCastingComplete);
        Task->ReadyForActivation();
    }
}

void UPCollectAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    check(ActorInfo && ActorInfo->AvatarActor.Get());

    //CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

void UPCollectAbility::OnCastingComplete(FGameplayTag EventTag, FGameplayEventData EventData)
{
    PM_LOG("jump")
    auto Hero = Cast<APHero>(GetAvatarActorFromActorInfo());
    Hero->Jump();
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}