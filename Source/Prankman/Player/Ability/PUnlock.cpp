#include "PUnlock.h"

#include "AbilitySystemComponent.h"
#include "Prankman/log.h"
#include "Prankman/Player/PHero.h"
#include "Prankman/Player/PPlayerController.h"
#include "Task/PCasting.h"

UPUnlockAbility::UPUnlockAbility()
{
}

bool UPUnlockAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    bool Activatable = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
    auto Hero = Cast<APHero>(GetAvatarActorFromActorInfo());
    auto AbilitiesCount = Cast<APPlayerController>(Hero->GetController())->Abilities.Num();
    Activatable = Activatable && Hero->GetVelocity().IsZero() && (AbilitiesCount < 4);
    if (!Activatable && (AbilitiesCount >= 4)) Cast<APPlayerController>(Hero->GetController())->NotifyError("You have too many abilities");
    return Activatable;
}

void UPUnlockAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
            return;
        }

        FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
        EffectContext.AddSourceObject(this);

        auto PHero = Cast<APHero>(GetAvatarActorFromActorInfo());
        FGameplayEffectSpecHandle EffectHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(PHero->UnlockEffect, 1, EffectContext);
        check(EffectHandle.IsValid())
        EffectHandle.Data->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag("Ability.Unlock"), CastingDuration);;
        PHero->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), PHero->GetAbilitySystemComponent());

        auto Task = UPCasting::Create(this, NAME_None, CastingDuration);
        Task->OnComplete.AddUObject(this, &UPUnlockAbility::OnCastingComplete);
        Task->ReadyForActivation();
    }
}

void UPUnlockAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    check(ActorInfo && ActorInfo->AvatarActor.Get());

    //CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

void UPUnlockAbility::OnCastingComplete(FGameplayTag EventTag, FGameplayEventData EventData)
{
    auto Hero = Cast<APHero>(GetAvatarActorFromActorInfo());
    Hero->Unlock();
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}