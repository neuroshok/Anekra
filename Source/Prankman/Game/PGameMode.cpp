#include "Prankman/Game/PGameMode.h"

#include "Prankman/World/PCell.h"
#include "Prankman/Player/PHero.h"
#include "Prankman/log.h"
#include "Prankman/Game/PGameState.h"
#include "GameFramework/PlayerState.h"
#include "Prankman/Player/PHUD.h"
#include "Prankman/Player/PPlayerController.h"

void APGameMode::BeginPlay()
{
    Super::BeginPlay();
    PM_LOG("APGameMode::BeginPlay")
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

void APGameMode::OnEventTimer()
{
    PM_LOG("TIMER")
    auto randomType = FMath::RandRange(static_cast<int32>(EPEventType::None), static_cast<int32>(EPEventType::Count) - 1);
    EventType = static_cast<EPEventType>(randomType);
    GetGameState<APGameState>()->ClientStartEvent(EventType);
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
    FVector SpawnLocation = CellsView[CellIndex]->GetActorLocation();
    SpawnLocation.Z = 1000;
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    const auto PlayerPawn = GetWorld()->SpawnActor<APHero>(BP_Hero, SpawnLocation, FRotator{ 0, 0, 0 }, Params);

    PlayerController->Possess(PlayerPawn);
    Cast<APPlayerController>(PlayerController)->InitializeHUD();
}

FString APGameMode::InitNewPlayer(APlayerController* PlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
    FString init = Super::InitNewPlayer(PlayerController, UniqueId, Options, Portal);
    check(BP_Hero);

    // make map when host join the game
    if (PlayerController->IsLocalPlayerController())
    {
        MakeMap();
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

APCell* APGameMode::GetCell(int X, int Y) const { return CellsView[X * MapSizeX + Y]; }