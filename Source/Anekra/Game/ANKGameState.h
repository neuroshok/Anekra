#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ANKGameState.generated.h"

UCLASS()
class ANEKRA_API AANKGameState : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEventUpdateDelegate, EEventType, EEventPhase);

public:
    AANKGameState();
    void OnUpdateIndexLocation();

    void MakeMap();

    UFUNCTION(NetMulticast, Reliable)
    void ClientUpdateEvent(EEventType EventType, EEventPhase EventPhase);

    UFUNCTION(BlueprintCallable)
    class ACell* GetCell(int X, int Y);
    UFUNCTION(BlueprintCallable)
    TArray<class ACell*> GetCells();
    UFUNCTION(BlueprintCallable)
    int GetMapCellCountX() const;
    UFUNCTION(BlueprintCallable)
    float GetMapCellSize() const;
    UFUNCTION(BlueprintCallable)
    float GetMapWidth() const;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class ACell> BP_Cell;

    FOnEventUpdateDelegate OnEventUpdateDelegate;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
    FTimerHandle UpdateIndexLocation;

    UPROPERTY(Replicated)
    TArray<class ACell*> Cells;
};