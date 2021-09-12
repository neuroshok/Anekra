#include "Anekra/UI/Game/WLog.h"

#include "Anekra/Log.h"
#include "Anekra/Game/ANKGameState.h"
#include "Components/RichTextBlock.h"

void UWLog::NativeConstruct()
{
    Super::NativeConstruct();
    Cast<AANKGameState>(GetWorld()->GetGameState())->OnPlayerNetStatusUpdateDelegate.AddUObject(this, &UWLog::OnPlayerNetStatusUpdated);
}

void UWLog::OnPlayerNetStatusUpdated(AANKPlayerState* Player, EPlayerNetStatus Status)
{
    FText Data;
    switch (Status)
    {
        case EPlayerNetStatus::Login:
            Data = FText::Format(NSLOCTEXT("Anekra", "PlayerJoin", "<hl>{0}</> joined the game"), FText::AsCultureInvariant(Player->GetPlayerName()));
            break;
        case EPlayerNetStatus::Logout:
            Data = FText::Format(NSLOCTEXT("Anekra", "PlayerLeft", "<hl>{0}</> left the game"), FText::AsCultureInvariant(Player->GetPlayerName()));
            break;
    case EPlayerNetStatus::Disconnected:
            Data = FText::Format(NSLOCTEXT("Anekra", "PlayerDisconnected", "<hl>{0}</> disconnected"), FText::AsCultureInvariant(Player->GetPlayerName()));
            break;
    }

    WText->SetText(Data);
}