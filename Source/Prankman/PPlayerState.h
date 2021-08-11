#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

UCLASS()
class PRANKMAN_API APPlayerState : public APlayerState
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateHealDelegate);

public:
    void ComputeCellPosition();

    void AddHealth(float Value);

    UFUNCTION()
    void OnUpdateHealth();

    UPROPERTY(Replicated, ReplicatedUsing = OnUpdateHealth)
    float Health = .1f;

    FUpdateHealDelegate UpdateHealDelegate;
    FIntVector CellPosition;
    bool bIsOut = false;
};