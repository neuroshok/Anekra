// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WFriends.generated.h"

/**
 * 
 */
UCLASS()
class ANEKRA_API UWFriends : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    class UScrollBox* WFriendsBox;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anekra|UI")
    TSubclassOf<UUserWidget> BP_WFriendRow;

protected:
    void NativeConstruct() override;
    void NativeDestruct() override;

private:
    void OnFriendListUpdated(const TArray<TSharedRef<class FOnlineFriend>>&);
    void OnRefresh();
    FTimerHandle RefreshTimer;
};