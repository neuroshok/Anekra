#pragma once

#include "CoreMinimal.h"
#include "PBinding.h"
#include "Abilities/GameplayAbility.h"
#include "PCollect.generated.h"

UCLASS()
class PRANKMAN_API UPCollectAbility : public UGameplayAbility
{
    GENERATED_BODY()

public:
    UPCollectAbility();

protected:
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayTagContainer* SourceTags = nullptr,
        const FGameplayTagContainer* TargetTags = nullptr,
        OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    //virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

private:
    UFUNCTION()
    void OnCastingComplete(FGameplayTag EventTag, FGameplayEventData EventData);

};