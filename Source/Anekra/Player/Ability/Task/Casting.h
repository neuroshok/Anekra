#pragma once

#include "Abilities/Tasks/AbilityTask.h"

#include "CoreMinimal.h"
#include "Casting.generated.h"

UCLASS()
class ANEKRA_API UCasting : public UAbilityTask
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCompleteDelegate, FGameplayTag, FGameplayEventData);
    DECLARE_MULTICAST_DELEGATE(FOnCancelDelegate);

public:
    UCasting();

    virtual void Activate() override;
    virtual void OnDestroy(bool bInOwnerFinished) override;

    void OnCancelled(FGameplayTag Tag, int32 Count);
    void OnCompleted();

    FOnCompleteDelegate OnCompleteDelegate;
    FOnCancelDelegate OnCancelDelegate;

    static UCasting* Create(UGameplayAbility* OwningAbility, float Duration);

private:
    FTimerHandle CastingTimer;
    float Duration;
};