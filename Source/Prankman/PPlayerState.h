#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

UCLASS()
class PRANKMAN_API APPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    void ComputeCellPosition();

    void AddHealth(float Value);
    FIntVector GetCellPosition() const;

public:
    UFUNCTION()
    void OnUpdateHealth();

    UPROPERTY(Replicated, ReplicatedUsing = OnUpdateHealth)
    float Health = .1f;

private:
    FIntVector CellPosition;
    bool bIsOut = false;
};