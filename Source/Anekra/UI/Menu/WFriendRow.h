#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WFriendRow.generated.h"

USTRUCT(BlueprintType)
struct FANKOnlineFriend
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Anekra")
    FString Name;
    UPROPERTY(BlueprintReadOnly, Category = "Anekra")
    bool bIsPlayingThisGame;
    UPROPERTY(BlueprintReadOnly, Category = "Anekra")
    bool bIsOnline;
};

UCLASS()
class ANEKRA_API UWFriendRow : public UUserWidget
{
    GENERATED_BODY()

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateDelegate, const FANKOnlineFriend&, Friend);

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WUserName;
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UTextBlock* WUserStatus;

    void SetFriend(TSharedRef<class FOnlineFriend> Friend);

    UPROPERTY(BlueprintAssignable, Category = "Anekra|Online|Friend")
    FOnUpdateDelegate OnUpdateDelegate;
};