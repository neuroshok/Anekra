#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ANKGameState.generated.h"

UCLASS()
class ANEKRA_API AANKGameState : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_OneParam(FOnEventDelegate, EEventType);

public:
    AANKGameState();
    void OnUpdateIndexLocation();

    UFUNCTION(NetMulticast, Reliable)
    void ClientStartEvent(EEventType EventType);

    FOnEventDelegate OnEventDelegate;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    FTimerHandle UpdateIndexLocation;
};