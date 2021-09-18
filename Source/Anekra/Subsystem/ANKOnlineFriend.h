#pragma once

#include "CoreMinimal.h"
#include "ANKOnlineFriend.generated.h"

UENUM(BlueprintType)
enum class EANKOnlinePresenceState : uint8
{
    Online,
    Offline,
    Away,
    ExtendedAway,
    DoNotDisturb,
    Chat
};

USTRUCT(BlueprintType)
struct FANKOnlineFriend
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category = "Anekra|Online|Friend")
    FString Name;
    UPROPERTY(BlueprintReadOnly, Category = "Anekra|Online|Friend")
    bool bIsPlaying;
    UPROPERTY(BlueprintReadOnly, Category = "Anekra|Online|Friend")
    bool bIsPlayingThisGame;
    UPROPERTY(BlueprintReadOnly, Category = "Anekra|Online|Friend")
    EANKOnlinePresenceState State;
};