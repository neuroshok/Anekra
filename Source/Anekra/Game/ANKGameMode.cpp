#include "Anekra/Game/ANKGameMode.h"

#include "EventSystem.h"
#include "Anekra/World/Cell.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Log.h"
#include "Anekra/PlayerNetStatus.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
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

    if (HasAuthority())
    {
        GetGameState<AANKGameState>()->MakeMap();

        EventSystem = NewObject<UEventSystem>(this, BP_EventSystem, "Event System");
        check(EventSystem);
        EventSystem->Initialize();
        //EventSystem->Start();
    }

    FVector SpawnLocation;
    SpawnLocation.X = 0;
    SpawnLocation.Y = 0;
    SpawnLocation.Z = 1000;
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    const auto PlayerPawn = GetWorld()->SpawnActor<AHero>(BP_Hero, SpawnLocation, FRotator{ 0, 0, 0 }, Params);

    PlayerController->Possess(PlayerPawn);
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

    //const int32 CellIndex = FMath::RandRange(0, CellsView.Num() - 1);
    //FVector SpawnLocation =  CellsView[CellIndex]->GetActorLocation();


    // if players.count == gamestate.players_count, start_game
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