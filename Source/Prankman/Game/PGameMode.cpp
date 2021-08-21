#include "Prankman/Game/PGameMode.h"

#include "PEventSystem.h"
#include "Prankman/World/PCell.h"
#include "Prankman/Player/PHero.h"
#include "Prankman/log.h"
#include "Prankman/Game/PGameState.h"
#include "Prankman/Player/PPlayerController.h"
#include "GameFramework/PlayerState.h"

void APGameMode::BeginPlay()
{
    Super::BeginPlay();
}

void APGameMode::MakeMap()
{
    if (!BP_Cell) PM_LOG("bp_cell not found")
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
                auto Cell = GetWorld()->SpawnActor<APCell>(BP_Cell, Position, FRotator{0, 0, 0}, params);
                if (!Cell)
                {
                    PM_ERROR("unable to make map")
                    break;
                }
                auto CellType = FMath::RandRange(0, static_cast<int8>(EPCellType::Count));
                //Cell->SetType(static_cast<EPCellType>(CellType));
                if (x == 0 && y == 0) Cell->SetType(EPCellType::Heal);
                if (x == 2 && y == 2) Cell->SetType(EPCellType::Burn);
                if (x == 1 && y == 0) Cell->SetType(EPCellType::Slow);
                CellsView.Add(Cell);
            }
        }
        PM_LOG("Map created with %d cells", CellsView.Num());
    }
}

void APGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
    PM_LOG("PreLogin");
    //FString id = UGameplayStatics::ParseOption(Options, TEXT("id"));
}

void APGameMode::PostLogin(APlayerController* PlayerController)
{
    Super::PostLogin(PlayerController);
    PM_LOG("PostLogin");

    const int32 CellIndex = FMath::RandRange(0, CellsView.Num() - 1);
    FVector SpawnLocation =  CellsView[CellIndex]->GetActorLocation();
    SpawnLocation.Z = 1000;
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    const auto PlayerPawn = GetWorld()->SpawnActor<APHero>(BP_Hero, SpawnLocation, FRotator{ 0, 0, 0 }, Params);

    PlayerController->Possess(PlayerPawn);
    Cast<APPlayerController>(PlayerController)->InitializeHUD();

    // if players.count == gamestate.players_count, start_game
}

FString APGameMode::InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
    FString init = Super::InitNewPlayer(PlayerController, UniqueId, Options, Portal);
    check(BP_Hero);

    //todo find a better place for init
    // make map when host join the game
    if (PlayerController->IsLocalPlayerController())
    {
        MakeMap();
        EventSystem = NewObject<UPEventSystem>(this, BP_EventSystem, "Event System");
        check(EventSystem);
        EventSystem->Start();
    }

    return init;
}

void APGameMode::Logout(AController* Controller)
{
    Super::Logout(Controller);
    UE_LOG(LogTemp, Warning, TEXT("Logout"));
}


float APGameMode::GetMapWidth() const { return MapSizeX * CellSize; }
float APGameMode::GetCellSize() const { return CellSize; }

APCell* APGameMode::GetCell(int X, int Y) const
{
    auto index = X * MapSizeX + Y;
    if (index >= CellsView.Num()) return nullptr;
    return CellsView[X * MapSizeX + Y];
}

TArray<APCell*> APGameMode::GetCells() const
{
    return CellsView;
}