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
    //GetGameState<AANKGameState>()->MakeMap();
}

void AANKGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
    Super::HandleStartingNewPlayer_Implementation(PlayerController);
    ANK_LOG("HandleStartingNewPlayer");

    GetGameState<AANKGameState>()->MakeMap();

    EventSystem = NewObject<UEventSystem>(this, BP_EventSystem, "Event System");
    check(EventSystem);
    EventSystem->Initialize();
    //EventSystem->Start();

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

bool AANKGameMode::ReadyToStartMatch_Implementation()
{
    const auto Session = GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->GetCurrentSession();
    // start game if player started without sessions or alone
    if (!Session) return true;
    else return (GetNumPlayers() == Session->RegisteredPlayers.Num() || Session->RegisteredPlayers.Num() <= 1);

    return false;
}

void AANKGameMode::StartMatch()
{
    Super::StartMatch();

    const auto CellSize = static_cast<int>(GetGameState<AANKGameState>()->GetMapCellSize());
    const auto MapWidth = static_cast<int>(GetGameState<AANKGameState>()->GetMapWidth());
    for (const auto Player : GetGameState<AANKGameState>()->GetPlayers())
    {
        FVector SpawnLocation;
        SpawnLocation.X = FMath::RandRange(CellSize, MapWidth - CellSize);
        SpawnLocation.Y = FMath::RandRange(CellSize, MapWidth - CellSize);
        SpawnLocation.Z = 1000;
        FActorSpawnParameters Params;
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        const auto PlayerPawn = GetWorld()->SpawnActor<AHero>(BP_Hero, SpawnLocation, FRotator{ 0, 0, 0 }, Params);

        Cast<AANKPlayerController>(Player->GetOwner())->Possess(PlayerPawn);
    }
}