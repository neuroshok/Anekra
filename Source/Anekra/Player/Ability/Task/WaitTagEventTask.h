#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "WaitTagEventTask.generated.h"

UCLASS()
class ANEKRA_API UWaitTagEventTask : public UAbilityTask
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE(FOnCompleteDelegate);

public:
    virtual void Activate() override;
    virtual void OnDestroy(bool bInOwnerFinished) override;

    void OnUpdated(FGameplayTag Tag, int32 Count);

    FOnCompleteDelegate OnCompleteDelegate;

    static UWaitTagEventTask* Create(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayTag Tag);

    FGameplayTag WaitingTag;
};