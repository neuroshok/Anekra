#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/Ability.h"
#include "CrossFireAbility.generated.h"

UCLASS()
class ANEKRA_API UCrossFireAbility : public UAbility
{
    GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;
};