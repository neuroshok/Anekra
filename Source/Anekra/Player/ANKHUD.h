// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Anekra/EventType.h"
#include "GameFramework/HUD.h"
#include "ANKHUD.generated.h"

/**
 * 
 */
UCLASS()
class ANEKRA_API AANKHUD : public AHUD
{
    GENERATED_BODY()

public:
    void Initialize();
    void Error(FString);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UUserWidget> BP_WMain;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    UPROPERTY()
    class UWMain* WMain;
    FTimerHandle MessageTimer;

    bool bInitialized = false;
};