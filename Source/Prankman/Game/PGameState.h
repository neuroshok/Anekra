#pragma once

#include "Prankman/PEventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PGameState.generated.h"

UCLASS()
class PRANKMAN_API APGameState : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateEventDelegate, EPEventType, EventType);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpdateHealthDelegate);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
    void OnEvent();

public:
    APGameState();
    void OnUpdateIndexLocation();

    UFUNCTION(NetMulticast, Reliable)
    void ClientStartEvent(EPEventType EventType);

    FUpdateEventDelegate UpdateEventDelegate;
    FUpdateHealthDelegate UpdateHealthDelegate;

private:
    FTimerHandle UpdateIndexLocation;
};