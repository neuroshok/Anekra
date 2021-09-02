#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/Ability.h"
#include "StealthAbility.generated.h"

UCLASS()
class ANEKRA_API UStealthAbility : public UAbility
{
    GENERATED_BODY()

public:
    UStealthAbility();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;

    void OnCompleted();
};