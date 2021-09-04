#include "Stealth.h"

#include "Anekra/Log.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Player/Hero.h"
#include "Task/WaitTagEventTask.h"

UStealthAbility::UStealthAbility()
{
    AbilityTags.AddTag(ANKTag.Ability.Stealth);
}

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

        GetAbilitySystemComponent()->ApplyEffect(GetAbilitySystemComponent()->Effects->StealthEffect);
        GetHero()->SetStealth();

        auto Task = UWaitTagEventTask::Create(this, ANKTag.Ability.Stealth);

        Task->OnCompleteDelegate.AddUObject(this, &UStealthAbility::OnCompleted);
        Task->ReadyForActivation();
    }
}

void UStealthAbility::OnCompleted()
{
    GetHero()->SetStealth(false);

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}