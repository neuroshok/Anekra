#include "Anekra/Player/ANKPlayerState.h"

#include "Anekra/Player/Attribute/Basic.h"
#include "Anekra/Game/ANKGameMode.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/Game/ANKAbilitySystemComponent.h"

#include "Net/UnrealNetwork.h"

AANKPlayerState::AANKPlayerState()
{
    NetUpdateFrequency = 100.0f;
    ANKAbilitySystemComponent = CreateDefaultSubobject<UANKAbilitySystemComponent>(FName("Ability System Component"));
    ANKAbilitySystemComponent->SetIsReplicated(true);
    ANKAbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Full;

    PAttributeBasic = CreateDefaultSubobject<UAttributeBasic>(TEXT("AttributeBasic"));
}

UAbilitySystemComponent* AANKPlayerState::GetAbilitySystemComponent() const
{
    return ANKAbilitySystemComponent;
}

void AANKPlayerState::ComputeCellPosition()
{
    check(GetPawn());
    float X = GetPawn()->GetActorLocation().X;
    float Y = GetPawn()->GetActorLocation().Y;

    auto ANKGameMode = Cast<AANKGameMode>(GetWorld()->GetAuthGameMode());
    const float MapWidth = ANKGameMode->GetMapWidth();
    const float CellSize = ANKGameMode->GetCellSize();

    float CellX = (X + CellSize / 2.f) / CellSize;
    float CellY = (Y + CellSize / 2.f) / CellSize;

    //bIsOut = false;
    //ANK_LOG("%f %f", CellX, CellY)
    if (CellX < 0 || CellX > CellSize - 1 || CellY < 0 || CellY > CellSize - 1)
    {
        //bIsOut = true;
        return;
    }

    CellPosition.X = static_cast<int32>(CellX);
    CellPosition.Y = static_cast<int32>(CellY);
}

FIntVector AANKPlayerState::GetCellPosition() const
{
    return CellPosition;
}