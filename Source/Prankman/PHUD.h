// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PEventType.h"
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
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class UUserWidget> BP_WEvent;

protected:
    virtual void BeginPlay() override;

private:
    UFUNCTION()
    void OnEvent(EPEventType Type);

    UPROPERTY()
    class UWEvent* WEvent;
};