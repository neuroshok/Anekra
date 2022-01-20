#include "Anekra/Game/ANKGameMode.h"

#include "EventSystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Anekra/World/Cell.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Log.h"
#include "Anekra/PlayerNetStatus.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "Anekra/Subsystem/OnlineSubsystem.h"
#include "GameFramework/PlayerState.h"

void AANKGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void AANKGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
    Super::HandleStartingNewPlayer_Implementation(PlayerController);
    ANK_LOG("HandleStartingNewPlayer");

    if (HasAuthority())
    {
        EventSystem = NewObject<UEventSystem>(this, BP_EventSystem, "Event System");
        check(EventSystem);
        EventSystem->Initialize();
        EventSystem->Start();

        PlayerControllers.Add(Cast<AANKPlayerController>(PlayerController));

        const auto Session = GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->GetCurrentSession();
        // start game if player started without sessions or alone
        if (!Session || GameStatus == EGameStatus::WaitingPlayers && GetNumPlayers() == Session->RegisteredPlayers.Num() || Session->RegisteredPlayers.Num() <= 1)
        {
            GetGameState<AANKGameState>()->MakeMap();
            StartGame();
        }
    }

    GetGameState<AANKGameState>()->ClientUpdatePlayers(Cast<AANKPlayerState>(PlayerController->PlayerState));
}

void AANKGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
    ANK_LOG("PreLogin");
    //FString id = UGameplayStatics::ParseOption(Options, TEXT("id"));
}

void AANKGameMode::PostLogin(APlayerController* PlayerController)
{
    Super::PostLogin(PlayerController);
    ANK_LOG("PostLogin");
}

FString AANKGameMode::InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
    FString init = Super::InitNewPlayer(PlayerController, UniqueId, Options, Portal);

    return init;
}

void AANKGameMode::Logout(AController* Controller)
{
    Super::Logout(Controller);
    ANK_LOG("Logout")
}

void AANKGameMode::RestartGame()
{
    StartGame();
}

void AANKGameMode::StartGame()
{
    // players
    const auto CellSize = static_cast<int>(GetGameState<AANKGameState>()->GetMapCellSize());
    const auto MapWidth = static_cast<int>(GetGameState<AANKGameState>()->GetMapWidth());
    for (const auto PlayerController : PlayerControllers)
    {
        FVector SpawnLocation;
        SpawnLocation.X = FMath::RandRange(CellSize, MapWidth - CellSize);
        SpawnLocation.Y = FMath::RandRange(CellSize, MapWidth - CellSize);
        SpawnLocation.Z = 1000;
        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        const auto PlayerPawn = GetWorld()->SpawnActor<AHero>(BP_Hero, SpawnLocation, FRotator{ 0, 0, 0 }, Params);

        PlayerController->InitializeHUD();
        PlayerController->Possess(PlayerPawn);
    }
}