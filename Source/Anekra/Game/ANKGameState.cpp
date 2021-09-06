#include "Anekra/Game/ANKGameState.h"

#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Game/ANKGameMode.h"
#include "Anekra/Game/ANKGameInstance.h"
#include "Anekra/World/Cell.h"
#include "Anekra/Log.h"
#include "Net/UnrealNetwork.h"

AANKGameState::AANKGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AANKGameState::CheckEndGame()
{
    int PlayersAlive = 0;
    for (auto Player : PlayerArray)
        PlayersAlive += Cast<AANKPlayerState>(Player)->IsAlive();

    if (PlayersAlive <= 1) ClientEndGame();
}

void AANKGameState::ClientEndGame_Implementation()
{
    OnGameStatusUpdateDelegate.Broadcast(EGameStatus::Finished);
}

// server
void AANKGameState::OnUpdateIndexLocation()
{
    for (const auto& Player : PlayerArray)
    {
        auto ANKPlayer = Cast<AANKPlayerState>(Player);
        if (ANKPlayer->IsDead() || !IsValid(ANKPlayer->GetPawn())) continue;

        auto PreviousCellPosition = ANKPlayer->GetCellPosition();
        ANKPlayer->ComputeCellPosition();

        if (ANKPlayer->GetPawn()->GetActorLocation().Z < -1000) ANKPlayer->Die();

        if (!ANKPlayer->IsDead())
        {
            // player cell position changed
            if (ANKPlayer->GetCellPosition() != PreviousCellPosition)
            {
                auto PreviousCell = Cast<AANKGameState>(GetWorld()->GetGameState())->GetCell(PreviousCellPosition);
                if (PreviousCell) PreviousCell->Leave(ANKPlayer);

                auto Cell = Cast<AANKGameState>(GetWorld()->GetGameState())->GetCell(ANKPlayer->GetCellPosition());
                if (Cell) Cell->Enter(ANKPlayer);
                // else player out
            }
        }
    }
}

// server
void AANKGameState::MakeMap()
{
    if (!BP_Cell) ANK_LOG("bp_cell not found")
    else
    {
        int Size = GetMapCellCountX();
        FVector Position;

        for (int x = 0; x < Size; ++x)
        {
            for (int y = 0; y < Size; ++y)
            {
                Position.X = x * MapCellSize;
                Position.Y = y * MapCellSize;
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
                Cells.Add(Cell);
            }
        }
        ANK_LOG("Map created with %d cells", Cells.Num());
    }
}

void AANKGameState::ClientUpdateEvent_Implementation(const EEventType EventType, EEventPhase EventPhase)
{
    OnEventUpdateDelegate.Broadcast(EventType, EventPhase);
}

float AANKGameState::GetMapWidth() const { return GetMapCellCountX() * MapCellSize; }
float AANKGameState::GetMapCellSize() const { return MapCellSize; }

ACell* AANKGameState::GetCell(const FIntVector& Position)
{
    auto index = Position.X * GetMapCellCountX() + Position.Y;
    if (index >= Cells.Num()) return nullptr;
    return Cells[Position.X * GetMapCellCountX() + Position.Y];
}

FIntVector AANKGameState::GetCellPosition(const FVector& Location)
{
    FIntVector Position;
    const float MapWidth = GetMapWidth();
    const float CellSize = GetMapCellSize();

    Position.X = (Location.X + CellSize / 2.f) / CellSize;
    Position.Y = (Location.Y + CellSize / 2.f) / CellSize;

    //return FIntVector::NoneValue;

    return Position;
}

TArray<ACell*> AANKGameState::GetCells()
{
    return Cells;
}

TArray<AANKPlayerState*> AANKGameState::GetPlayersAtCellPosition(const FIntVector& Position)
{
    TArray<AANKPlayerState*> Array;
    for (auto PlayerState : PlayerArray)
    {
        auto ANKPlayerState = Cast<AANKPlayerState>(PlayerState);
        if (ANKPlayerState->GetCellPosition().X == Position.X && ANKPlayerState->GetCellPosition().Y == Position.Y)
            Array.Add(ANKPlayerState);
    }
    return Array;
}

TArray<AANKPlayerState*> AANKGameState::GetPlayersAtCellPositionExclude(const FIntVector& Position, const APlayerState* ExcludedPlayerState)
{
    TArray<AANKPlayerState*> Array;
    for (auto PlayerState : PlayerArray)
    {
        auto ANKPlayerState = Cast<AANKPlayerState>(PlayerState);
        if (ExcludedPlayerState->GetPlayerId() == ANKPlayerState->GetPlayerId()) continue;
        if (ANKPlayerState->GetCellPosition().X == Position.X && ANKPlayerState->GetCellPosition().Y == Position.Y)
            Array.Add(ANKPlayerState);
    }
    return Array;
}

int AANKGameState::GetMapCellCountX() const
{
    return MapCellCountX;
}

TArray<APlayerState*> AANKGameState::GetPlayers() const
{
    return PlayerArray;
}

TArray<AANKPlayerState*> AANKGameState::GetPlayersAlive() const
{
    TArray<AANKPlayerState*> Players;
    for (auto Player : PlayerArray)
    {
        auto ANKPlayer = Cast<AANKPlayerState>(Player);
        if (ANKPlayer->IsAlive()) Players.Add(ANKPlayer);
    }
    return Players;
}

void AANKGameState::BeginPlay()
{
    Super::BeginPlay();
}

void AANKGameState::Tick(float DeltaSeconds)
{
    if (GetWorld()->IsServer()) OnUpdateIndexLocation();
}

void AANKGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AANKGameState, Cells);
}

void AANKGameState::AddPlayerState(APlayerState* PlayerState)
{
    Super::AddPlayerState(PlayerState);
    //PlayerState->SetPlayerName(FString{ "Arkena" } + FString::FromInt(PlayerState->GetPlayerId()));
    OnPlayerNetStatusUpdateDelegate.Broadcast(Cast<AANKPlayerState>(PlayerState), EPlayerNetStatus::Login);
}

void AANKGameState::RemovePlayerState(APlayerState* PlayerState)
{
    Super::RemovePlayerState(PlayerState);
    OnPlayerNetStatusUpdateDelegate.Broadcast(Cast<AANKPlayerState>(PlayerState), EPlayerNetStatus::Logout);
}