#include "Unlock.h"

#include "AbilitySystemComponent.h"
#include "Anekra/Log.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Task/Casting.h"

UUnlockAbility::UUnlockAbility()
{
}


bool UUnlockAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                        const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    bool Activatable = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
    auto Hero = Cast<AHero>(GetAvatarActorFromActorInfo());
    auto AbilitiesCount = Cast<AANKPlayerController>(Hero->GetController())->Abilities.Num();
    Activatable = Activatable && Hero->GetVelocity().IsZero() && (AbilitiesCount < 4);
    if (!Activatable && (AbilitiesCount >= 4)) Cast<AANKPlayerController>(Hero->GetController())->NotifyError("You have too many abilities");
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

        auto Hero = Cast<AHero>(GetAvatarActorFromActorInfo());
        GetAbilitySystemComponent()->PlayMontage(this, ActivationInfo, Hero->UnlockMontage, 1);

        auto EffectHandle = GetAbilitySystemComponent()->ApplyEffectSpec(GetAbilitySystemComponent()->Effects->UnlockEffect);
        auto Task = UCasting::Create(this, NAME_None, EffectHandle.Data->Duration);

        Task->OnCompleteDelegate.AddUObject(this, &UUnlockAbility::OnCastingCompleted);
        Task->OnCancelDelegate.AddLambda([this, Handle, ActorInfo, ActivationInfo]() { CancelAbility(Handle, ActorInfo, ActivationInfo, true); });
        Task->ReadyForActivation();
    }
}

void UUnlockAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
    GetAbilitySystemComponent()->CurrentMontageStop();
    auto ANKPlayerState = Cast<AANKPlayerState>(ActorInfo->PlayerController->PlayerState);
    ANKPlayerState->OnCastingCancelDelegate.Broadcast();

    Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UUnlockAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    check(ActorInfo && ActorInfo->AvatarActor.Get());

    //CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

void UUnlockAbility::OnCastingCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
    GetAbilitySystemComponent()->CurrentMontageStop();

    auto ANKPlayerController = Cast<AANKPlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
    check(ANKPlayerController);
    // unlock server side
    ANKPlayerController->Unlock();
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}