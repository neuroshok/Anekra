#include "Anekra/Game/ANKGameMode.h"

#include "EventSystem.h"
#include "Anekra/World/Cell.h"
#include "Anekra/Player/Hero.h"
#include "Anekra/Log.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Player/ANKPlayerController.h"
#include "GameFramework/PlayerState.h"

void AANKGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void AANKGameMode::MakeMap()
{
    if (!BP_Cell) ANK_LOG("bp_cell not found")
    else
    {
        int Size = MapSizeX;
        FVector Position;

        for (int x = 0; x < Size; ++x)
        {
            for (int y = 0; y < Size; ++y)
            {
                Position.X = x * CellSize;
                Position.Y = y * CellSize;
                FActorSpawnParameters params;
                params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
                auto Cell = GetWorld()->SpawnActor<ACell>(BP_Cell, Position, FRotator{0, 0, 0}, params);
                if (!Cell)
                {
                    ANK_ERROR("unable to make map")
                    break;
                }
                auto CellType = FMath::RandRange(0, static_cast<int8>(ECellType::Count));
                //Cell->SetType(static_cast<ECellType>(CellType));
                if (x == 0 && y == 0) Cell->SetType(ECellType::Heal);
                if (x == 2 && y == 2) Cell->SetType(ECellType::Burn);
                if (x == 1 && y == 0) Cell->SetType(ECellType::Slow);
                CellsView.Add(Cell);
            }
        }
        ANK_LOG("Map created with %d cells", CellsView.Num());
    }
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

    const int32 CellIndex = FMath::RandRange(0, CellsView.Num() - 1);
    FVector SpawnLocation =  CellsView[CellIndex]->GetActorLocation();
    SpawnLocation.Z = 1000;
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    const auto PlayerPawn = GetWorld()->SpawnActor<AHero>(BP_Hero, SpawnLocation, FRotator{ 0, 0, 0 }, Params);

    PlayerController->Possess(PlayerPawn);

    // if players.count == gamestate.players_count, start_game
}

FString AANKGameMode::InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
    FString init = Super::InitNewPlayer(PlayerController, UniqueId, Options, Portal);
    check(BP_Hero);

    //todo find a better place for init
    // make map when host join the game
    if (PlayerController->IsLocalPlayerController())
    {
        MakeMap();
        EventSystem = NewObject<UEventSystem>(this, BP_EventSystem, "Event System");
        check(EventSystem);
        EventSystem->Start();
    }

    return init;
}

void AANKGameMode::Logout(AController* Controller)
{
    Super::Logout(Controller);
    UE_LOG(LogTemp, Warning, TEXT("Logout"));
}


float AANKGameMode::GetMapWidth() const { return MapSizeX * CellSize; }
float AANKGameMode::GetCellSize() const { return CellSize; }

ACell* AANKGameMode::GetCell(int X, int Y) const
{
    auto index = X * MapSizeX + Y;
    if (index >= CellsView.Num()) return nullptr;
    return CellsView[X * MapSizeX + Y];
}

TArray<ACell*> AANKGameMode::GetCells() const
{
    return CellsView;
}