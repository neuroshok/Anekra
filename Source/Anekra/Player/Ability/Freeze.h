#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/ANKAbility.h"
#include "Freeze.generated.h"

UCLASS()
class ANEKRA_API UFreezeAbility : public UANKAbility
{
    GENERATED_BODY()

protected:
    UFreezeAbility();
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;
};