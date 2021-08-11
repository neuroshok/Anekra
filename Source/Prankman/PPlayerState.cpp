#include "PPlayerState.h"

#include "log.h"
#include "PGameMode.h"
#include "Net/UnrealNetwork.h"

void APPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APPlayerState, Health);
}

void APPlayerState::ComputeCellPosition()
{
    check(GetPawn());
    float X = GetPawn()->GetActorLocation().X;
    float Y = GetPawn()->GetActorLocation().Y;

    auto PGameMode = Cast<APGameMode>(GetWorld()->GetAuthGameMode());
    const float MapWidth = PGameMode->GetMapWidth();
    const float CellSize = PGameMode->GetCellSize();

    float CellX = (X + CellSize / 2.f) / CellSize;
    float CellY = (Y + CellSize / 2.f) / CellSize;

    bIsOut = false;
    //PM_LOG("%f %f", CellX, CellY)
    if (CellX < 0 || CellX > CellSize - 1 || CellY < 0 || CellY > CellSize - 1)
    {
        bIsOut = true;
        return;
    }

    CellPosition.X = static_cast<int32>(CellX);
    CellPosition.Y = static_cast<int32>(CellY);
}

void APPlayerState::AddHealth(float Value)
{
    Health += Value;
    OnUpdateHealth();
}

void APPlayerState::OnUpdateHealth()
{
    UpdateHealDelegate.Broadcast();
}