#include "WFriendRow.h"

#include "OnlineSubsystemTypes.h"
#include "Anekra/Subsystem/OnlineSubsystem.h"
#include "Components/TextBlock.h"
#include "Interfaces/OnlinePresenceInterface.h"

void UWFriendRow::SetFriend(TSharedRef<FOnlineFriend> Friend)
{
    FText StatusText = EOnlinePresenceState::ToLocText(Friend->GetPresence().Status.State);

    WUserName->SetText(FText::AsCultureInvariant(Friend->GetDisplayName()));
    WUserStatus->SetText(StatusText);

    FANKOnlineFriend BPFriend;
    BPFriend.Name = Friend->GetDisplayName();
    BPFriend.bIsPlayingThisGame = Friend->GetPresence().bIsPlayingThisGame;
    BPFriend.bIsOnline = Friend->GetPresence().bIsOnline;
    OnUpdateDelegate.Broadcast(BPFriend);

    switch(Friend->GetPresence().Status.State)
    {
    case EOnlinePresenceState::Away:
        WUserStatus->SetColorAndOpacity(FLinearColor{ 1, 1, 0, 1 });
        break;
    case EOnlinePresenceState::DoNotDisturb:
        WUserStatus->SetColorAndOpacity(FLinearColor{ 1, 0, 0, 1 });
        break;
    case EOnlinePresenceState::Online:
            WUserStatus->SetColorAndOpacity(FLinearColor{ 0, 1, 0, 1 });
        break;
    case EOnlinePresenceState::Offline:
            WUserStatus->SetColorAndOpacity(FLinearColor{ 0.2, 0.2, 0.2, 1 });
        break;
    default:;
    }

    if (Friend->GetPresence().bIsPlaying)
    {
        WUserStatus->SetColorAndOpacity(FLinearColor{ 0, 0, 1, 1 });
        WUserStatus->SetText(NSLOCTEXT("OnlineSystem", "Playing", "Playing"));
    }
    else if (Friend->GetPresence().bIsPlayingThisGame)
    {
        WUserStatus->SetColorAndOpacity(FLinearColor{ 1, 0, 1, 1 });
        WUserStatus->SetText(NSLOCTEXT("OnlineSystem", "PlayingThis", "Anekra"));
    }
}