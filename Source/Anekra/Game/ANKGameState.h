#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "Anekra/Player/ANKPlayerState.h"
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

    // Cell
    UFUNCTION(BlueprintCallable)
    class ACell* GetCell(int X, int Y);
    UFUNCTION(BlueprintCallable)
    TArray<class ACell*> GetCells();
    UFUNCTION(BlueprintCallable)
    TArray<class AANKPlayerState*> GetPlayersAtCellPosition(const FIntVector& Position);
    UFUNCTION(BlueprintCallable)
    TArray<class AANKPlayerState*> GetPlayersAtCellPositionExclude(const FIntVector& Position, const APlayerState* ExcludedPlayerState);

    // Map
    UFUNCTION(BlueprintCallable)
    int GetMapCellCountX() const;
    UFUNCTION(BlueprintCallable)
    float GetMapCellSize() const;
    UFUNCTION(BlueprintCallable)
    float GetMapWidth() const;

    FOnEventUpdateDelegate OnEventUpdateDelegate;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra|Map")
    int MapCellCountX = 10;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra|Map")
    float MapCellSize = 800.f;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class ACell> BP_Cell;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

private:
    FTimerHandle UpdateIndexLocation;

    UPROPERTY(Replicated)
    TArray<class ACell*> Cells;
};