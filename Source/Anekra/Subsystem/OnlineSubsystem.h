#pragma once

#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "CoreMinimal.h"
#include "ANKOnlineFriend.h"
#include "Interfaces/OnlinePresenceInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSubsystem.generated.h"

UENUM(BlueprintType)
enum class EFriendLoop : uint8
{
    Body,
    Completed
};

UCLASS(BlueprintType, Blueprintable)
class ANEKRA_API UOnlineSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConnectionStatusChanged, const FString& /*ServiceName*/, EOnlineServerConnectionStatus::Type /*LastConnectionState*/, EOnlineServerConnectionStatus::Type /*ConnectionState*/);
    typedef FOnConnectionStatusChanged::FDelegate FOnConnectionStatusChangedDelegate;

    // Friend
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendListCompleteDelegate, const TArray<TSharedRef<FOnlineFriend>>&);

    // Presence
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPresenceUpdateDelegate, const FANKOnlineFriend&, Presence);

    // Session
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSessionCreateDelegate, FName, SessionName, bool, Success);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSessionParticipantsUpdateDelegate);

public:
    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Session")
    void CreateSession();

    void Invite(const FUniqueNetId& FriendId);

    UFUNCTION(BlueprintCallable, Category = "Anekra|Online")
    FString GetLocalUserName(int32 LocalPlayer = 0) const;
    //UFUNCTION(BlueprintCallable, Category = "Anekra|Online")
    FString GetUserName(const FUniqueNetId& UniqueNetId) const;

    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Friends")
    UPARAM(DisplayName="Success") bool GetFriends();

    FOnFriendListCompleteDelegate OnFriendListCompleteDelegate;

    UPROPERTY(BlueprintAssignable)
    FOnSessionCreateDelegate OnSessionCreated;
    UPROPERTY(BlueprintAssignable)
    FOnSessionParticipantsUpdateDelegate OnSessionParticipantsUpdateDelegate;
    UPROPERTY(BlueprintAssignable)
    FOnPresenceUpdateDelegate OnPresenceUpdateDelegate;

protected:
    UOnlineSubsystem();
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    //
    void OnConnectionStatusChanged(const FString& ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState, EOnlineServerConnectionStatus::Type ConnectionState);
    FOnConnectionStatusChangedDelegate OnConnectionStatusChangedDelegate;

    // Friends
    void OnFriendsChanged();
    void OnReadFriendsListCompleted(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);
    FOnFriendsChangeDelegate OnFriendsChangeDelegate;
    FOnReadFriendsListComplete OnReadFriendsListCompleteDelegate;

    // Presence
    void OnPresenceReceived(const class FUniqueNetId& UserId, const TSharedRef<FOnlineUserPresence>& Presence);
    FOnPresenceReceivedDelegate OnPresenceReceivedDelegate;

    // Session
    void OnCreateSessionCompleted(FName SessionName, bool Successful);
    void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);
    void OnRegisterPlayersCompleted(FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Players, bool bWasSuccessful);
    void OnSessionInviteReceived(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId, const FOnlineSessionSearchResult& InviteResult);
    void OnSessionParticipantsUpdated(FName SessionName, const FUniqueNetId& UserId, bool JoinLeave);
    void OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult);
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
    FOnRegisterPlayersCompleteDelegate OnRegisterPlayersCompleteDelegate;
    FOnSessionInviteReceivedDelegate OnSessionInviteReceivedDelegate;
    FOnSessionParticipantsChangeDelegate OnSessionParticipantsChangeDelegate;
    FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;

private:
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;

    class IOnlineSubsystem* OSS = nullptr;
    TSharedPtr<FOnlineSessionSettings> Settings;
};