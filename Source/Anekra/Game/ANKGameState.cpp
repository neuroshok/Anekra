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

// server
void AANKGameState::OnUpdateIndexLocation()
{
    for (const auto& Player : PlayerArray)
    {
        auto ANKPlayer = Cast<AANKPlayerState>(Player);
        if (ANKPlayer->IsDead()) continue;

        auto PreviousCellPosition = ANKPlayer->GetCellPosition();
        ANKPlayer->ComputeCellPosition();

        if (ANKPlayer->GetPawn()->GetActorLocation().Z < -1000)
        {
            ANKPlayer->Die();
        }

        if (!ANKPlayer->IsDead())
        {
            // player cell position changed
            if (ANKPlayer->GetCellPosition() != PreviousCellPosition)
            {
                auto PreviousCell = Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PreviousCellPosition.X, PreviousCellPosition.Y);
                if (PreviousCell) PreviousCell->Leave(ANKPlayer);

                auto Cell = Cast<AANKGameMode>(GetWorld()->GetAuthGameMode())->GetCell(ANKPlayer->GetCellPosition().X, ANKPlayer->GetCellPosition().Y);
                if (Cell) Cell->Enter(ANKPlayer);
                // else player out
            }
        }
    }
}

void AANKGameState::ClientStartEvent_Implementation(const EEventType EventType)
{
    OnEventDelegate.Broadcast(EventType);
}