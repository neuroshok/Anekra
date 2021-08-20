#include "Prankman/Game/PGameState.h"

#include "Prankman/Player/PPlayerState.h"
#include "Prankman/Game/PGameMode.h"
#include "Prankman/World/PCell.h"
#include "Prankman/log.h"

APGameState::APGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APGameState::BeginPlay()
{
    Super::BeginPlay();
}

void APGameState::Tick(float DeltaSeconds)
{
    if (GetWorld()->IsServer()) OnUpdateIndexLocation();
}

/// server
void APGameState::OnUpdateIndexLocation()
{
    for (const auto& Player : PlayerArray)
    {
        auto PPlayer = Cast<APPlayerState>(Player);
        auto PreviousCellPosition = PPlayer->GetCellPosition();
        PPlayer->ComputeCellPosition();

        // player cell position changed
        if (PPlayer->GetCellPosition() != PreviousCellPosition)
        {
            auto PreviousCell = Cast<APGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PreviousCellPosition.X, PreviousCellPosition.Y);
            PreviousCell->Leave(PPlayer);

            auto Cell = Cast<APGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PPlayer->GetCellPosition().X, PPlayer->GetCellPosition().Y);
            if (Cell) Cell->Enter(PPlayer);
            // else player out
        }
    }
}

void APGameState::ClientStartEvent_Implementation(const EPEventType EventType)
{
    OnEventDelegate.Broadcast(EventType);
}