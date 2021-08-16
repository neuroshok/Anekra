#pragma once

#include "Abilities/Tasks/AbilityTask.h"

#include "CoreMinimal.h"
#include "PCasting.generated.h"

UCLASS()
class PRANKMAN_API UPCasting : public UAbilityTask
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCompleteDelegate, FGameplayTag, FGameplayEventData);

public:
    UPCasting();

    virtual void Activate() override;

    UFUNCTION()
    void OnEndCasting();

    FOnCompleteDelegate OnComplete;

    static UPCasting* Create(UGameplayAbility* OwningAbility, FName TaskInstanceName, float Duration);

private:
    FTimerHandle CastingTimer;
    float Duration;
};