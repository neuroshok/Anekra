#include "WFriendRow.h"

#include "Anekra/Subsystem/ANKOnlineFriend.h"

#include "OnlineSubsystemTypes.h"
#include "Anekra/Subsystem/OnlineSubsystem.h"
#include "Components/TextBlock.h"
#include "Interfaces/OnlinePresenceInterface.h"

void UWFriendRow::SetFriend(TSharedRef<FOnlineFriend> FriendRef)
{
    FriendPtr = FriendRef;

    FANKOnlineFriend Friend;
    Friend.Name = FriendPtr->GetDisplayName();
    Friend.bIsPlayingThisGame = FriendPtr->GetPresence().bIsPlayingThisGame;
    Friend.bIsPlaying = FriendPtr->GetPresence().bIsPlaying;
    Friend.State = (EANKOnlinePresenceState)(uint8)FriendPtr->GetPresence().Status.State;
    OnFriendUpdated(Friend);

    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->OnPresenceUpdateDelegate.AddDynamic(this, &UWFriendRow::OnPresenceUpdated);
}

void UWFriendRow::OnFriendUpdated_Implementation(const FANKOnlineFriend& Friend)
{
}

void UWFriendRow::Invite()
{
    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->Invite(*FriendPtr->GetUserId());
}

void UWFriendRow::OnPresenceUpdated(const FANKOnlineFriend& Friend)
{
    OnFriendUpdated(Friend);
}