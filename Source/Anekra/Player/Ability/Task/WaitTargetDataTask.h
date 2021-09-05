#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "WaitTargetDataTask.generated.h"

UCLASS(MinimalAPI)
class UWaitTargetDataTask : public UAbilityTask
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompleteDelegate, FVector);

public:
    virtual void Activate() override;

    void OnClick();

    static UWaitTargetDataTask* Create(UGameplayAbility* OwningAbility);

    UFUNCTION(BlueprintCallable, Category = "Anekra|Task", meta = (DisplayName="LaserTargetTask", DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "true"))
    static UWaitTargetDataTask* Create(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner);

    FOnCompleteDelegate OnCompleteDelegate;
    FDelegateHandle OnTargetDataReplicatedCallbackDelegate;

private:
    FHitResult ComputeTargetLocation();
    void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
    void CompleteTask();
};