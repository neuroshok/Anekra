#pragma once

#include "CoreMinimal.h"
#include "Anekra/Player/ANKAbility.h"
#include "LaserBurst.generated.h"

UCLASS()
class ANEKRA_API ULaserBurst : public UANKAbility
{
    GENERATED_BODY()

protected:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle, const FGameplayAbilityActorInfo*, const FGameplayAbilityActivationInfo, const FGameplayEventData*) override;

private:
    void OnCompleted(FVector);
};