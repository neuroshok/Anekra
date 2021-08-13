#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

UCLASS()
class PRANKMAN_API APPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

    APPlayerState();
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:
    void ComputeCellPosition();

    void AddHealth(float Value);
    FIntVector GetCellPosition() const;

    //
    UPROPERTY()
    class UAbilitySystemComponent* AbilitySystemComponent;

    //
    UFUNCTION()
    void OnUpdateHealth();

    UPROPERTY(Replicated, ReplicatedUsing = OnUpdateHealth)
    float Health = .1f;

private:
    FIntVector CellPosition;
    bool bIsOut = false;
};