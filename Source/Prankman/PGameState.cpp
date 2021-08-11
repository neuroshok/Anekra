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
    int i = 0;
    for (const auto& Player : PlayerArray)
    {
        auto PPlayer = Cast<APPlayerState>(Player);
        auto PreviousCell = Cast<APGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PPlayer->CellPosition.X, PPlayer->CellPosition.Y);

        PPlayer->ComputeCellPosition();

        auto Cell = Cast<APGameMode>(GetWorld()->GetAuthGameMode())->GetCell(PPlayer->CellPosition.X, PPlayer->CellPosition.Y);
        PreviousCell->PlayersOver.Reset();
        Cell->AddPlayerOver(PPlayer);

        //if (i == 0) Cell->SetColor({0, 255, 0});
        //else Cell->SetColor({255, 0, 0});

        ++i;
    }
}

void APGameState::ClientStartEvent_Implementation(EPEventType EventType)
{
    EventDelegate.Broadcast(EventType);
}