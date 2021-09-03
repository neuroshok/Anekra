#include "Anekra/Game/ANKGameState.h"

#include "Constant.h"
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

// server
void AANKGameState::OnUpdateIndexLocation()
{
    for (const auto& Player : PlayerArray)
    {
        auto ANKPlayer = Cast<AANKPlayerState>(Player);
        if (ANKPlayer->IsDead()) continue;

        auto PreviousCellPosition = ANKPlayer->GetCellPosition();
        ANKPlayer->ComputeCellPosition();

        if (ANKPlayer->GetPawn()->GetActorLocation().Z < -1000) ANKPlayer->Die();

        if (!ANKPlayer->IsDead())
        {
            // player cell position changed
            if (ANKPlayer->GetCellPosition() != PreviousCellPosition)
            {
                auto PreviousCell = Cast<AANKGameState>(GetWorld()->GetGameState())->GetCell(PreviousCellPosition.X, PreviousCellPosition.Y);
                if (PreviousCell) PreviousCell->Leave(ANKPlayer);

                auto Cell = Cast<AANKGameState>(GetWorld()->GetGameState())->GetCell(ANKPlayer->GetCellPosition().X, ANKPlayer->GetCellPosition().Y);
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

ACell* AANKGameState::GetCell(int X, int Y)
{
    auto index = X * GetMapCellCountX() + Y;
    if (index >= Cells.Num()) return nullptr;
    return Cells[X * GetMapCellCountX() + Y];
}

TArray<ACell*> AANKGameState::GetCells()
{
    return Cells;
}

TArray<AANKPlayerState*> AANKGameState::GetPlayersAtCellPosition(int X, int Y)
{
    TArray<AANKPlayerState*> Array;
    for (auto PlayerState : PlayerArray)
    {
        auto ANKPlayerState = Cast<AANKPlayerState>(PlayerState);
        if (ANKPlayerState->GetCellPosition().X == X && ANKPlayerState->GetCellPosition().Y == Y)
            Array.Add(ANKPlayerState);
    }
    return Array;
}

int AANKGameState::GetMapCellCountX() const
{
    return MapCellCountX;
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