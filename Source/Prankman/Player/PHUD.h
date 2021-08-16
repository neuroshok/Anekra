// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Prankman/PEventType.h"
#include "GameFramework/HUD.h"
#include "PHUD.generated.h"

/**
 * 
 */
UCLASS()
class PRANKMAN_API APHUD : public AHUD
{
    GENERATED_BODY()

public:
    void Initialize();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class UUserWidget> BP_WMain;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    UFUNCTION()
    void OnUpdateEvent(EPEventType Type);

    UPROPERTY()
    class UWMain* WMain;

    bool bInitialized = false;
};