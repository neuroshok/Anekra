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

    DECLARE_MULTICAST_DELEGATE(FOnDataUpdateDelegate);

public:
    AANKPlayerState();

    virtual UANKAbilitySystemComponent* GetAbilitySystemComponent() const override;

    void Initialize();
    void Die();

    void ComputeCellPosition();
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    FIntVector GetCellPosition() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    bool IsDead() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    bool IsAlive() const;

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
    FOnDataUpdateDelegate OnDataUpdateDelegate;

protected:
    virtual void BeginPlay() override;
    virtual void OnRep_PlayerName() override;

private:
    FIntVector CellPosition;
    bool bIsDead = false;
};