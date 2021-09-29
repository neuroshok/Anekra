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
    Friend.Id = FriendRef->GetUserId()->ToString();
    Friend.Name = FriendPtr->GetDisplayName();
    Friend.bIsPlayingThisGame = FriendPtr->GetPresence().bIsPlayingThisGame;
    Friend.bIsPlaying = FriendPtr->GetPresence().bIsPlaying;
    Friend.State = (EANKOnlinePresenceState)(uint8)FriendPtr->GetPresence().Status.State;
    OnFriendUpdated(Friend);
}

TSharedPtr<FOnlineFriend> UWFriendRow::GetFriend() const
{
    return FriendPtr;
}

void UWFriendRow::OnFriendUpdated_Implementation(const FANKOnlineFriend& Friend)
{
}

void UWFriendRow::Invite()
{
    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->Invite(*FriendPtr->GetUserId());
}