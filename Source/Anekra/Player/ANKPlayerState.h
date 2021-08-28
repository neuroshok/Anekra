#pragma once

#include "AbilitySystemInterface.h"
#include "Anekra/Game/ANKAbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ANKPlayerState.generated.h"

UCLASS()
class ANEKRA_API AANKPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCastingDelegate, float);

public:
    AANKPlayerState();

    virtual UANKAbilitySystemComponent* GetAbilitySystemComponent() const override;

    void Die();

    void ComputeCellPosition();
    FIntVector GetCellPosition() const;
    bool IsDead() const;

    UFUNCTION(Client, Reliable)
    void ClientDie();

    FOnCastingDelegate OnCastingDelegate;

    //
    UPROPERTY()
    class UANKAbilitySystemComponent* ANKAbilitySystemComponent;
    UPROPERTY()
    class UAttributeBasic* PAttributeBasic;

    //

private:
    FIntVector CellPosition;
    bool bIsDead = false;
};