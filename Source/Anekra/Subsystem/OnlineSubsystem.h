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
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBP_OnPresenceUpdateDelegate, const FANKOnlineFriend&, Presence);

    // Session
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBP_OnCreateSessionDelegate, FName, SessionName, bool, Success);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBP_OnDestroySessionCompleteDelegate, FName, SessionName, bool, Success);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBP_OnJoinSessionCompleteDelegate, FName, SessionName/*, EOnJoinSessionCompleteResult::Type, JoinResult*/);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FBP_OnSessionParticipantsUpdateDelegate, const FString&, UserId, const FString&, UserName, bool, JoinLeave);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBP_OnStartSessionCompleteDelegate, FName, SessionName, bool, Success);

public:
    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Session")
    void CreateSession();
    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Session")
    void DestroySession();
    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Session")
    void StartSession();

    void Invite(const FUniqueNetId& FriendId);

    UFUNCTION(BlueprintCallable, Category = "Anekra|Online")
    FString GetLocalUserName(int32 LocalPlayer = 0) const;
    //UFUNCTION(BlueprintCallable, Category = "Anekra|Online")
    FString GetUserName(const FUniqueNetId& UniqueNetId) const;
    class FNamedOnlineSession* GetCurrentSession() const;

    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Friends")
    UPARAM(DisplayName="Success") bool GetFriends();

    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Session")
    TArray<FString> GetSessionPlayers();

    FOnFriendListCompleteDelegate OnFriendListCompleteDelegate;

    // friend
    UPROPERTY(BlueprintAssignable, Category = "Anekra|Online|Session", meta = (DisplayName = "Event Presence Updated", CompactNodeTitle = "EventPresenceUpdated"))
    FBP_OnPresenceUpdateDelegate BP_OnPresenceUpdateDelegate;
    // session
    UPROPERTY(BlueprintAssignable, Category = "Anekra|Online|Session", meta = (DisplayName = "Event Session Create", CompactNodeTitle = "EventSessionCreate"))
    FBP_OnCreateSessionDelegate BP_OnCreateSessionDelegate;
    UPROPERTY(BlueprintAssignable, Category = "Anekra|Online|Session", meta = (DisplayName = "Event Session Destroy", CompactNodeTitle = "EventSessionDestroy"))
    FBP_OnDestroySessionCompleteDelegate BP_OnDestroySessionCompleteDelegate;
    UPROPERTY(BlueprintAssignable, Category = "Anekra|Online|Session", meta = (DisplayName = "Event Session Participants Update", CompactNodeTitle = "EventSessionParticipantsUpdate"))
    FBP_OnSessionParticipantsUpdateDelegate BP_OnSessionParticipantsUpdateDelegate;
    UPROPERTY(BlueprintAssignable, Category = "Anekra|Online|Session", meta = (DisplayName = "Event Session Joined", CompactNodeTitle = "EventSessionJoined"))
    FBP_OnJoinSessionCompleteDelegate BP_OnJoinSessionCompleteDelegate;
    UPROPERTY(BlueprintAssignable, Category = "Anekra|Online|Session", meta = (DisplayName = "Event Session Started", CompactNodeTitle = "EventSessionStarted"))
    FBP_OnStartSessionCompleteDelegate BP_OnStartSessionCompleteDelegate;

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
    void OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful);
    void OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful);
    void OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult);
    void OnRegisterPlayersCompleted(FName SessionName, const TArray< TSharedRef<const FUniqueNetId> >& Players, bool bWasSuccessful);
    void OnSessionInviteReceived(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId, const FOnlineSessionSearchResult& InviteResult);
    void OnSessionParticipantsUpdated(FName SessionName, const FUniqueNetId& UserId, bool JoinLeave);
    void OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult);
    void OnStartSessionCompleted(FName SessionName, bool bWasSuccessful);
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
    FOnRegisterPlayersCompleteDelegate OnRegisterPlayersCompleteDelegate;
    FOnSessionInviteReceivedDelegate OnSessionInviteReceivedDelegate;
    FOnSessionParticipantsChangeDelegate OnSessionParticipantsChangeDelegate;
    FOnSessionUserInviteAcceptedDelegate OnSessionUserInviteAcceptedDelegate;
    FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

private:
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;

    class IOnlineSubsystem* OSS = nullptr;
    TSharedPtr<FOnlineSessionSettings> Settings;
};