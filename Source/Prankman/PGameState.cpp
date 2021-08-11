#include "PGameState.h"

#include "PPlayerState.h"
#include "PGameMode.h"
#include "PCell.h"
#include "log.h"

APGameState::APGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APGameState::BeginPlay()
{
    Super::BeginPlay();
    if (GetWorld()->IsServer())
    {
        //GetWorldTimerManager().SetTimer(UpdateIndexLocation, this, &APGameState::OnUpdateIndexLocation, 0.1f, true);
    }
}

void APGameState::Tick(float DeltaSeconds)
{
    if (GetWorld()->IsServer()) OnUpdateIndexLocation();
}

void APGameState::OnEvent()
{

}


// server
void APGameState::OnUpdateIndexLocation()
{
    /// server
    int i = 0;
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
            // PreviousCell->PlayersOver.Reset();

            auto Cell = Cast<APGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PPlayer->GetCellPosition().X, PPlayer->GetCellPosition().Y);
            Cell->Enter(PPlayer)
            Cell->AddPlayerOver(PPlayer);
        }


        //if (i == 0) Cell->SetColor({0, 255, 0});
        //else Cell->SetColor({255, 0, 0});

        ++i;
    }
}

void APGameState::ClientStartEvent_Implementation(const EPEventType EventType)
{
    UpdateEventDelegate.Broadcast(EventType);
}