#pragma once

#include "PEventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGameMode.generated.h"

UCLASS()
class PRANKMAN_API APGameMode final : public AGameModeBase
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    void MakeMap();
    void OnEventTimer();

    void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
    void PostLogin(APlayerController*);
    FString InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal);
    void Logout(AController*);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class APCell> BP_Cell;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class APHero> BP_Hero;

private:
    TArray<class APCell*> CellsView;

    FTimerHandle EventTimer;
    EPEventType EventType;
};