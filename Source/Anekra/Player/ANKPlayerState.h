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
    DECLARE_MULTICAST_DELEGATE(FOnCastingCancelDelegate);

public:
    AANKPlayerState();

    virtual UANKAbilitySystemComponent* GetAbilitySystemComponent() const override;

    void Die();
    void SetStealth();

    void OnStealthUpdated(FGameplayTag Tag, int32 Count);

    void ComputeCellPosition();
    FIntVector GetCellPosition() const;
    bool IsDead() const;

    FOnCastingDelegate OnCastingDelegate;
    FOnCastingCancelDelegate OnCastingCancelDelegate;

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