#pragma once

#include "CoreMinimal.h"
#include "Prankman/Player/PAbility.h"
#include "PUnlock.generated.h"

UCLASS()
class PRANKMAN_API UPUnlockAbility : public UPAbility
{
    GENERATED_BODY()

public:
    UPUnlockAbility();

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

    float CastingDuration = 2;
};