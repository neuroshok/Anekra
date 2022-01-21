#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "Anekra/GameStatus.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "GameFramework/GameMode.h"
#include "ANKGameMode.generated.h"

UCLASS()
class ANEKRA_API AANKGameMode final : public AGameModeBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class AHero> BP_Hero;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UEventSystem> BP_EventSystem;

    // match
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void EndGame();
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void RestartGame();
    UFUNCTION(BlueprintCallable, Category = "Anekra")
    void StartGame();

protected:
    virtual void BeginPlay() override;

    virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
    virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
    virtual void PostLogin(APlayerController*) override;
    virtual FString InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
    virtual void Logout(AController*) override;

private:
    UPROPERTY()
    class UEventSystem* EventSystem;

    UPROPERTY()
    TArray<class AANKPlayerController*> PlayerControllers;

    EGameStatus GameStatus = EGameStatus::WaitingPlayers;
};