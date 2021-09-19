#pragma once

#include "Anekra/Subsystem/ANKOnlineFriend.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WFriendRow.generated.h"

UCLASS(BlueprintType)
class ANEKRA_API UWFriendRow : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetFriend(TSharedRef<class FOnlineFriend> Friend);

    UFUNCTION(BlueprintNativeEvent, Category = "Anekra|Online|Friend")
    void OnFriendUpdated(const FANKOnlineFriend& Friend);

    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Friend")
    void Invite();

protected:
    UFUNCTION()
    void OnPresenceUpdated(const FANKOnlineFriend& Friend);

private:
    TSharedPtr<FOnlineFriend> FriendPtr;
};