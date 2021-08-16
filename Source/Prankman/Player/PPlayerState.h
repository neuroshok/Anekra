#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPlayerState.generated.h"

UCLASS()
class PRANKMAN_API APPlayerState : public APlayerState, public IAbilitySystemInterface
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnCastingDelegate, float);

public:
    APPlayerState();

    virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    void ComputeCellPosition();
    FIntVector GetCellPosition() const;

    FOnCastingDelegate OnCastingDelegate;

    //
    UPROPERTY()
    class UPAbilitySystemComponent* PAbilitySystemComponent;
    UPROPERTY()
    class UPAttributeBasic* PAttributeBasic;

private:
    FIntVector CellPosition;
};