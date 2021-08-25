#pragma once

#include "Abilities/Tasks/AbilityTask.h"

#include "CoreMinimal.h"
#include "Casting.generated.h"

UCLASS()
class ANEKRA_API UCasting : public UAbilityTask
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCompleteDelegate, FGameplayTag, FGameplayEventData);

public:
    UCasting();

    virtual void Activate() override;

    UFUNCTION()
    void OnEndCasting();

    FOnCompleteDelegate OnComplete;

    static UCasting* Create(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration);

private:
    FTimerHandle CastingTimer;
    float Duration;
};