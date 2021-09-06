#include "WEndGame.h"

#include "Anekra/Game/ANKGameState.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UWEndGame::Update()
{
    FText StatusText;

    AANKPlayerState* Winner = nullptr;
    for (auto Player : Cast<AANKGameState>(GetWorld()->GetGameState())->GetPlayersAlive())
    {
        Winner = Player;
    }

    if (!Winner) return;

    StatusText = FText::Format(NSLOCTEXT("Anekra", "PlayerWin", "{0} wins !"), FText::FromString(Winner->GetPlayerName()));
    WStatusText->SetText(StatusText);
}

void UWEndGame::NativeConstruct()
{
    Super::NativeConstruct();
    if (GetWorld()->GetFirstPlayerController()->HasAuthority())
    {
        WPlayAgain->SetVisibility(ESlateVisibility::Visible);
    }
    else WPlayAgain->SetVisibility(ESlateVisibility::Hidden);
}