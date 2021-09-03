#include "Unlock.h"

#include "AbilitySystemComponent.h"
#include "Anekra/Log.h"
#include "Anekra/Game/Constant.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Task/Casting.h"

UUnlockAbility::UUnlockAbility()
{
    AbilityTags.AddTag(ANKTag.Ability.Unlock);

    BlockAbilitiesWithTag.AddTag(ANKTag.Ability.Root);
    CancelAbilitiesWithTag.AddTag(ANKTag.Ability.Root);
    ActivationOwnedTags.AddTag(ANKTag.State.Casting);
    ActivationOwnedTags.AddTag(ANKTag.Ability.Unlock);
}


bool UUnlockAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    bool Activatable = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
    auto Hero = Cast<AHero>(GetAvatarActorFromActorInfo());
    auto AbilitiesCountMax = GetANKPlayerController()->GetAbilitiesCountMax();
    auto AbilitiesCount = GetANKPlayerController()->GetAbilitiesCount();
    Activatable = Activatable && Hero->GetVelocity().IsZero() && (AbilitiesCount < AbilitiesCountMax);
    if (!Activatable && (AbilitiesCount >= AbilitiesCountMax)) Cast<AANKPlayerController>(Hero->GetController())->NotifyError("You have too many abilities");
    return Activatable;
}

void UUnlockAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                     const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
            return;
        }

        GetAbilitySystemComponent()->PlayMontage(this, ActivationInfo, Montage, 1);

        //auto EffectHandle = GetAbilitySystemComponent()->ApplyEffectSpec(GetEffects()->CastingEffect);
        auto Task = UCasting::Create(this, CastingTime);

        Task->OnCompleteDelegate.AddUObject(this, &UUnlockAbility::OnCastingCompleted);
        Task->OnCancelDelegate.AddLambda([this, Handle, ActorInfo, ActivationInfo]() { CancelAbility(Handle, ActorInfo, ActivationInfo, true); });
        Task->ReadyForActivation();
    }
}

void UUnlockAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
    GetAbilitySystemComponent()->CurrentMontageStop();
    if (GetANKPlayerState()) GetANKPlayerState()->OnCastingCancelDelegate.Broadcast();

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UUnlockAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{

}

void UUnlockAbility::OnCastingCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
    GetAbilitySystemComponent()->CurrentMontageStop();

    // unlock server side
    GetANKPlayerController()->Unlock();
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}