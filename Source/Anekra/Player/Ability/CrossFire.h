#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/ANKAbility.h"
#include "CrossFire.generated.h"

UCLASS()
class ANEKRA_API UCrossFireAbility : public UANKAbility
{
    GENERATED_BODY()

public:
    UCrossFireAbility();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;
};