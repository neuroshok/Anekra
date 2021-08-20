#pragma once

#include "Prankman/PEventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PGameState.generated.h"

UCLASS()
class PRANKMAN_API APGameState : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnEventDelegate, EPEventType);

public:
    APGameState();
    void OnUpdateIndexLocation();

    UFUNCTION(NetMulticast, Reliable)
    void ClientStartEvent(EPEventType EventType);

    FOnEventDelegate OnEventDelegate;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    FTimerHandle UpdateIndexLocation;
};