// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"

#include "Anekra/EventType.h"
#include "GameFramework/HUD.h"
#include "ANKHUD.generated.h"

enum class EGameStatus : uint8;
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
    void ShowStats();
    void HideStats();

    void OnGameStatusUpdated(EGameStatus Status);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UUserWidget> BP_WMain;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UUserWidget> BP_WEndGame;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UUserWidget> BP_WGameStats;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

private:
    UPROPERTY()
    class UWEndGame* WEndGame;
    UPROPERTY()
    class UWGameStats* WGameStats;
    UPROPERTY()
    class UWMain* WMain;

    FTimerHandle MessageTimer;
    bool bInitialized = false;
};