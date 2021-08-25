#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/Ability.h"
#include "Freeze.generated.h"

UCLASS()
class ANEKRA_API UFreezeAbility : public UAbility
{
    GENERATED_BODY()

protected:

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;
};