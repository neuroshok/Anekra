#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/ANKAbility.h"
#include "Unlock.generated.h"

UCLASS()
class ANEKRA_API UUnlockAbility : public UANKAbility
{
    GENERATED_BODY()

public:
    UUnlockAbility();

protected:
    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
        const FGameplayAbilityActorInfo* ActorInfo,
        const FGameplayTagContainer* SourceTags = nullptr,
        const FGameplayTagContainer* TargetTags = nullptr,
        OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;
    virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
    virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
    //virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    float CastingTime = 1.f;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    class UAnimMontage* Montage;

private:
    UFUNCTION()
    void OnCastingCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

    FDelegateHandle CancelHandle;
};