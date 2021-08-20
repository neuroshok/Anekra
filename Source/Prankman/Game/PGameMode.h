#pragma once

#include "Prankman/PEventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PGameMode.generated.h"

UCLASS()
class PRANKMAN_API APGameMode final : public AGameModeBase
{
    GENERATED_BODY()

public:
    float GetMapWidth() const;
    float GetCellSize() const;
    class APCell* GetCell(int X, int Y) const;
    TArray<class APCell*> GetCells() const;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class APCell> BP_Cell;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class APHero> BP_Hero;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Prankman")
    TSubclassOf<class UPEventSystem> BP_EventSystem;

protected:
    virtual void BeginPlay() override;

    virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
    virtual void PostLogin(APlayerController*) override;
    virtual FString InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
    virtual void Logout(AController*) override;

    void MakeMap();

private:
    // todo use weakptr ?
    TArray<class APCell*> CellsView;

    UPROPERTY()
    class UPEventSystem* EventSystem;

    const int MapSizeX = 10;
    const float CellSize = 400.f;
};