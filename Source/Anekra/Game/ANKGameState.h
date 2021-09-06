#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "Anekra/GameStatus.h"
#include "Anekra/PlayerNetStatus.h"
#include "Anekra/Player/ANKPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "ANKGameState.generated.h"

UCLASS()
class ANEKRA_API AANKGameState : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerNetStatusUpdateDelegate, class AANKPlayerState*, EPlayerNetStatus);

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStatusUpdateDelegate, EGameStatus);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnEventUpdateDelegate, EEventType, EEventPhase);

public:
    AANKGameState();

    void CheckEndGame();
    UFUNCTION(Client, NetMulticast, Reliable)
    void ClientEndGame();

    FOnGameStatusUpdateDelegate OnGameStatusUpdateDelegate;

    // Event
    UFUNCTION(Client, NetMulticast, Reliable)
    void ClientUpdateEvent(EEventType EventType, EEventPhase EventPhase);
    FOnEventUpdateDelegate OnEventUpdateDelegate;

    // Cell
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    class ACell* GetCell(const FIntVector& CellPosition);
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    FIntVector GetCellPosition(const FVector& Location);
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    TArray<class ACell*> GetCells();
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    TArray<class AANKPlayerState*> GetPlayersAtCellPosition(const FIntVector& Position);
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    TArray<class AANKPlayerState*> GetPlayersAtCellPositionExclude(const FIntVector& Position, const APlayerState* ExcludedPlayerState);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class ACell> BP_Cell;

    // Map
    void MakeMap();

    UFUNCTION(BlueprintCallable, Category = "Anekra")
    int GetMapCellCountX() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    float GetMapCellSize() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    float GetMapWidth() const;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra|Map")
    int MapCellCountX = 10;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra|Map")
    float MapCellSize = 800.f;

    // Player
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    TArray<class APlayerState*> GetPlayers() const;
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    TArray<class AANKPlayerState*> GetPlayersAlive() const;

    FOnPlayerNetStatusUpdateDelegate OnPlayerNetStatusUpdateDelegate;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

    virtual void AddPlayerState(APlayerState* PlayerState);
    virtual void RemovePlayerState(APlayerState* PlayerState);

private:
    void OnUpdateIndexLocation();

    FTimerHandle UpdateIndexLocation;

    UPROPERTY(Replicated)
    TArray<class ACell*> Cells;
};