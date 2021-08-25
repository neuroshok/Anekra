#pragma once

#include "AbilitySystemInterface.h"
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

    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    void ComputeCellPosition();
    FIntVector GetCellPosition() const;

    FOnCastingDelegate OnCastingDelegate;

    //
    UPROPERTY()
    class UANKAbilitySystemComponent* ANKAbilitySystemComponent;
    UPROPERTY()
    class UAttributeBasic* PAttributeBasic;

private:
    FIntVector CellPosition;
};