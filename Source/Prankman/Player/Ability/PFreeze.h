#pragma once

#include "CoreMinimal.h"
#include "Prankman/Player/PAbility.h"
#include "PFreeze.generated.h"

UCLASS()
class PRANKMAN_API UPFreezeAbility : public UPAbility
{
    GENERATED_BODY()

protected:

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;
};