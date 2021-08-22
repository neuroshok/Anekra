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

        auto PHero = Cast<APHero>(GetAvatarActorFromActorInfo());

        FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
        EffectContext.AddSourceObject(this);

        FGameplayEffectSpecHandle EffectHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(PHero->UnlockEffect, 1, EffectContext);
        check(EffectHandle.IsValid())
        GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), GetAbilitySystemComponent());
        auto Task = UPCasting::Create(this, NAME_None, EffectHandle.Data->Duration);
        Task->OnComplete.AddUObject(this, &UPUnlockAbility::OnCastingComplete);
        Task->ReadyForActivation();

        GetAbilitySystemComponent()->PlayMontage(this, ActivationInfo, PHero->UnlockMontage, 1);
    }
}

void UPUnlockAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
    check(ActorInfo && ActorInfo->AvatarActor.Get());

    //CancelAbility(Handle, ActorInfo, ActivationInfo, true);
}

void UPUnlockAbility::OnCastingComplete(FGameplayTag EventTag, FGameplayEventData EventData)
{
    GetAbilitySystemComponent()->CurrentMontageStop();

    auto PPlayerController = Cast<APPlayerController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
    check(PPlayerController);
    // unlock server side
    if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority) PPlayerController->Unlock();
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}