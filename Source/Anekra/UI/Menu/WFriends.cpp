#include "Anekra/UI/Menu/WFriends.h"

#include "Anekra/Subsystem/OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "WFriendRow.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"

void UWFriends::NativeConstruct()
{
    Super::NativeConstruct();
    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->OnFriendListCompleteDelegate.AddUObject(this, &UWFriends::OnFriendListUpdated);
    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->BP_OnPresenceUpdateDelegate.AddDynamic(this, &UWFriends::OnPresenceUpdated);
}

void UWFriends::NativeDestruct()
{
    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->OnFriendListCompleteDelegate.RemoveAll(this);
    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->BP_OnPresenceUpdateDelegate.RemoveAll(this);
}

void UWFriends::OnFriendListUpdated(const TArray<TSharedRef<FOnlineFriend>>& Friends)
{
    WFriendsBox->ClearChildren();

    for (auto Friend : Friends)
    {
        auto Entry = CreateWidget<UWFriendRow>(GetWorld(), BP_WFriendRow);
        Entry->SetFriend(Friend);

        WFriendsBox->AddChild(Entry);
    }
}

void UWFriends::OnRefresh()
{
    GetWorld()->GetGameInstance()->GetSubsystem<UOnlineSubsystem>()->GetFriends();
}


void UWFriends::OnPresenceUpdated(const FANKOnlineFriend& Friend)
{
    for (auto WFriendRow : WFriendsBox->GetAllChildren())
    {
        if (Cast<UWFriendRow>(WFriendRow)->GetFriend()->GetUserId()->ToString() == Friend.Id)
        {
            Cast<UWFriendRow>(WFriendRow)->OnFriendUpdated(Friend);
            break;
        }
    }
}