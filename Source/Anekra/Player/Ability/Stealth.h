#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/ANKAbility.h"
#include "Stealth.generated.h"

UCLASS()
class ANEKRA_API UStealthAbility : public UANKAbility
{
    GENERATED_BODY()

public:
    UStealthAbility();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;

    void OnCompleted();
};