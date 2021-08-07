// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PEventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PGameState.generated.h"

UCLASS()
class PRANKMAN_API APGameState : public AGameStateBase
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDelegate, EPEventType, EventType);

public:
    UFUNCTION(NetMulticast, Reliable)
    void ClientStartEvent(EPEventType EventType);

protected:
    virtual void BeginPlay() override;
    void OnEvent();

public:
    FEventDelegate EventDelegate;
};