#include "Anekra/UI/WGameStats.h"

#include "Anekra/Log.h"
#include "Anekra/Game/ANKGameState.h"
#include "Anekra/UI/WGameStatsEntry.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

class UWGameStatsEntry;

void UWGameStats::Update()
{
    if (GetWorld()->bIsTearingDown) return;
    auto ANKGameState = Cast<AANKGameState>(GetWorld()->GetGameState());

    WStats->ClearChildren();
    int i = 0;
    for (auto Player : ANKGameState->GetPlayers())
    {
        auto Entry = CreateWidget<UWGameStatsEntry>(GetWorld(), BP_WGameStatsEntry);
        if (i++ % 2 == 0) Entry->WBorder->SetBrushColor(Entry->WBorder->BrushColor + FLinearColor{-0.2, -0.2, -0.2, 0});
        Entry->WName->SetText(FText::AsCultureInvariant(Player->GetPlayerName()));
        Entry->WKills->SetText(FText::AsNumber(99));
        Entry->WPing->SetText(FText::AsNumber(Player->GetPing()));
        WStats->AddChildToVerticalBox(Entry);
    }
}

void UWGameStats::NativeConstruct()
{
    Super::NativeConstruct();

    auto ANKGameState = Cast<AANKGameState>(GetWorld()->GetGameState());

    ANKGameState->OnPlayerNetStatusUpdateDelegate.AddLambda([this](auto...) { Update(); });
    Update();
}