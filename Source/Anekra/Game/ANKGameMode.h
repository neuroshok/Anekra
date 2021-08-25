#pragma once

#include "Anekra/EventType.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ANKGameMode.generated.h"

UCLASS()
class ANEKRA_API AANKGameMode final : public AGameModeBase
{
    GENERATED_BODY()

public:
    float GetMapWidth() const;
    float GetCellSize() const;
    class ACell* GetCell(int X, int Y) const;
    TArray<class ACell*> GetCells() const;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class ACell> BP_Cell;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class AHero> BP_Hero;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra")
    TSubclassOf<class UEventSystem> BP_EventSystem;

protected:
    virtual void BeginPlay() override;

    virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
    virtual void PostLogin(APlayerController*) override;
    virtual FString InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;
    virtual void Logout(AController*) override;

    void MakeMap();

private:
    // todo use weakptr ?
    TArray<class ACell*> CellsView;

    UPROPERTY()
    class UEventSystem* EventSystem;

    const int MapSizeX = 10;
    const float CellSize = 800.f;
};