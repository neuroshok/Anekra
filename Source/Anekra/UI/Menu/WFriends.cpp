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
    GetWorld()->GetTimerManager().SetTimer(RefreshTimer, this, &UWFriends::OnRefresh, 5, true);
}

void UWFriends::NativeDestruct()
{
    GetWorld()->GetTimerManager().ClearTimer(RefreshTimer);
    Super::NativeDestruct();
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