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

    void ComputeCellPosition();
    UFUNCTION(BlueprintCallable)
    FIntVector GetCellPosition() const;
    UFUNCTION(BlueprintCallable)
    bool IsDead() const;

    FOnCastingDelegate OnCastingDelegate;
    FOnCastingCancelDelegate OnCastingCancelDelegate;

    FDelegateHandle OnHealthUpdateDelegate;

    void OnHealthUpdated(const FOnAttributeChangeData& Data);

    //
    UPROPERTY()
    class UANKAbilitySystemComponent* ANKAbilitySystemComponent;
    UPROPERTY()
    class UAttributeBasic* AttributeBasic;

    //

protected:
    virtual void BeginPlay() override;

private:
    FIntVector CellPosition;
    bool bIsDead = false;
};