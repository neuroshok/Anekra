#include "StealthAbility.h"

#include "Anekra/Log.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Player/Hero.h"
#include "Task/WaitTagEventTask.h"

void UStealthAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                      const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* GameplayEventData)
{
    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
        {
            EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
            return;
        }

        GetAbilitySystemComponentFromActorInfo()->SetRemoveAbilityOnEnd(Handle);

        auto Hero = Cast<AHero>(GetAvatarActorFromActorInfo());
        GetAbilitySystemComponent()->ApplyEffect(GetAbilitySystemComponent()->Effects->StealthEffect);
        Hero->SetStealth();

        Cast<AANKPlayerController>(Hero->GetController())->RemoveAbility(Handle);

        auto Task = UWaitTagEventTask::Create(this, NAME_None, ANKTag.Ability.Stealth);

        Task->OnCompleteDelegate.AddUObject(this, &UStealthAbility::OnCompleted);
        Task->ReadyForActivation();
    }
}

void UStealthAbility::OnCompleted()
{
    Cast<AHero>(GetAvatarActorFromActorInfo())->SetStealth(false);

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}