#include "Anekra/Game/ANKGameState.h"

#include "Anekra/Player/ANKPlayerState.h"
#include "Anekra/Game/ANKGameMode.h"
#include "Anekra/World/Cell.h"
#include "Anekra/Log.h"

AANKGameState::AANKGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AANKGameState::BeginPlay()
{
    Super::BeginPlay();
}

void AANKGameState::Tick(float DeltaSeconds)
{
    if (GetWorld()->IsServer()) OnUpdateIndexLocation();
}

/// server
void AANKGameState::OnUpdateIndexLocation()
{
    for (const auto& Player : PlayerArray)
    {
        auto PPlayer = Cast<AANKPlayerState>(Player);
        auto PreviousCellPosition = PPlayer->GetCellPosition();
        PPlayer->ComputeCellPosition();

        // player cell position changed
        if (PPlayer->GetCellPosition() != PreviousCellPosition)
        {
            auto PreviousCell = Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PreviousCellPosition.X, PreviousCellPosition.Y);
            PreviousCell->Leave(PPlayer);

            auto Cell = Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PPlayer->GetCellPosition().X, PPlayer->GetCellPosition().Y);
            if (Cell) Cell->Enter(PPlayer);
            // else player out
        }
    }
}

void AANKGameState::ClientStartEvent_Implementation(const EEventType EventType)
{
    OnEventDelegate.Broadcast(EventType);
}