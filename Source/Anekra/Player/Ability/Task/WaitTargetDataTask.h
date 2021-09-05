#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "LaserTargetTask.generated.h"

UCLASS(MinimalAPI)
class ULaserTargetTask : public UAbilityTask
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCompleteDelegate, FVector);

public:
    virtual void Activate() override;

    void OnClick();

    static ULaserTargetTask* Create(UGameplayAbility* OwningAbility);

    UFUNCTION(BlueprintCallable, Category = "Anekra|Task", meta = (DisplayName="LaserTargetTask", DefaultToSelf = "TaskOwner", BlueprintInternalUseOnly = "true"))
    static ULaserTargetTask* Create(TScriptInterface<IGameplayTaskOwnerInterface> TaskOwner);

    FOnCompleteDelegate OnCompleteDelegate;
    FDelegateHandle OnTargetDataReplicatedCallbackDelegate;

private:
    FHitResult ComputeTargetLocation();
    void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);
    void CompleteTask();
};