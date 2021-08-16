#include "Prankman/Player/PPlayerState.h"

#include "Prankman/Player/Attribute/PBasic.h"
#include "Prankman/Game/PGameMode.h"
#include "Prankman/Game/PGameState.h"
#include "Prankman/Game/PAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

APPlayerState::APPlayerState()
{
    NetUpdateFrequency = 100.0f;
    PAbilitySystemComponent = CreateDefaultSubobject<UPAbilitySystemComponent>(FName("Ability System Component"));
    PAbilitySystemComponent->SetIsReplicated(true);
    PAbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Full;

    PAttributeBasic = CreateDefaultSubobject<UPAttributeBasic>(TEXT("AttributeBasic"));
}

UAbilitySystemComponent* APPlayerState::GetAbilitySystemComponent() const
{
    return PAbilitySystemComponent;
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

    //bIsOut = false;
    //PM_LOG("%f %f", CellX, CellY)
    if (CellX < 0 || CellX > CellSize - 1 || CellY < 0 || CellY > CellSize - 1)
    {
        //bIsOut = true;
        return;
    }

    CellPosition.X = static_cast<int32>(CellX);
    CellPosition.Y = static_cast<int32>(CellY);
}

FIntVector APPlayerState::GetCellPosition() const
{
    return CellPosition;
}