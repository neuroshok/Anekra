#include "Anekra/Subsystem/OnlineSubsystem.h"

#include "OnlineSubsystemUtils.h"
#include "Anekra/Log.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameUserSettings.h"

void UOnlineSubsystem::CreateSession()
{
    Settings = MakeShareable(new FOnlineSessionSettings);
    Settings->bUseLobbiesIfAvailable = true;
    Settings->NumPrivateConnections = 3;
    Settings->NumPublicConnections = 3;
    Settings->bShouldAdvertise = true;
    Settings->bAllowJoinInProgress = true;
    Settings->bIsLANMatch = false;
    Settings->bIsDedicated = false;
    Settings->bUsesStats = true;
    Settings->bAllowInvites = true;
    Settings->bUsesPresence = true;
    Settings->bAllowJoinViaPresence = true;
    Settings->bAllowJoinViaPresenceFriendsOnly = true;
    Settings->bAntiCheatProtected = false;
    Settings->BuildUniqueId = true;
    Settings->Set(SETTING_MAPNAME, FString("Your Level Name"), EOnlineDataAdvertisementType::DontAdvertise);

    OnCreateSessionCompleteDelegateHandle = OSS->GetSessionInterface()->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

    bool Status = OSS->GetSessionInterface()->CreateSession(0, "ANK TEST", *Settings);
    if (!Status)
    {
        ANK_ERROR("CreateSession failed")
        OSS->GetSessionInterface()->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
        BP_OnCreateSessionDelegate.Broadcast("ANK TEST", false);
    }
}

void UOnlineSubsystem::DestroySession()
{
    OSS->GetSessionInterface()->DestroySession("ANK TEST", OnDestroySessionCompleteDelegate);
}

void UOnlineSubsystem::StartSession()
{
    ANK_LOG("Start session")

    OSS->GetSessionInterface()->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);
    OSS->GetSessionInterface()->StartSession("ANK TEST");
}

void UOnlineSubsystem::Invite(const FUniqueNetId& FriendId)
{
    ANK_LOG("invite friend %s", *FriendId.ToDebugString())
    OSS->GetSessionInterface()->SendSessionInviteToFriend(0, "ANK TEST", FriendId);
}

FString UOnlineSubsystem::GetLocalUserName(int LocalPlayer) const
{
    return *OSS->GetIdentityInterface()->GetPlayerNickname(LocalPlayer);
}

FString UOnlineSubsystem::GetUserName(const FUniqueNetId& UniqueNetId) const
{
    return *OSS->GetIdentityInterface()->GetPlayerNickname(UniqueNetId);
}

bool UOnlineSubsystem::GetFriends()
{
    bool Success = false;
    if (OSS->GetFriendsInterface())
    {
        Success = OSS->GetFriendsInterface()->ReadFriendsList(0, "Friends", OnReadFriendsListCompleteDelegate);
        if (!Success) ANK_WARNING("ReadFriendList failed")
    }
    return Success;
}

UOnlineSubsystem::UOnlineSubsystem()
    : OnConnectionStatusChangedDelegate(FOnConnectionStatusChangedDelegate::CreateUObject(this, &UOnlineSubsystem::OnConnectionStatusChanged))
    // Friends
    , OnFriendsChangeDelegate(FOnFriendsChangeDelegate::CreateUObject(this, &UOnlineSubsystem::OnFriendsChanged))
    , OnReadFriendsListCompleteDelegate(FOnReadFriendsListComplete::CreateUObject(this, &UOnlineSubsystem::OnReadFriendsListCompleted))
    // Presence
    , OnPresenceReceivedDelegate(FOnPresenceReceivedDelegate::CreateUObject(this, &UOnlineSubsystem::OnPresenceReceived))
    // Session
    , OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineSubsystem::OnCreateSessionCompleted))
    , OnDestroySessionCompleteDelegate(FOnDestroySessionCompleteDelegate::CreateUObject(this, &UOnlineSubsystem::OnDestroySessionCompleted))
    , OnJoinSessionCompleteDelegate(FOnJoinSessionCompleteDelegate::CreateUObject(this, &UOnlineSubsystem::OnJoinSessionCompleted))
    , OnRegisterPlayersCompleteDelegate(FOnRegisterPlayersCompleteDelegate::CreateUObject(this, &UOnlineSubsystem::OnRegisterPlayersCompleted))
    , OnSessionInviteReceivedDelegate(FOnSessionInviteReceivedDelegate::CreateUObject(this, &UOnlineSubsystem::OnSessionInviteReceived))
    , OnSessionParticipantsChangeDelegate(FOnSessionParticipantsChangeDelegate::CreateUObject(this, &UOnlineSubsystem::OnSessionParticipantsUpdated))
    , OnSessionUserInviteAcceptedDelegate(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &UOnlineSubsystem::OnSessionUserInviteAccepted))
    , OnStartSessionCompleteDelegate(FOnStartSessionCompleteDelegate::CreateUObject(this, &UOnlineSubsystem::OnStartSessionCompleted))
{
    OSS = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
    if (!OSS) OSS = IOnlineSubsystem::Get(NULL_SUBSYSTEM);
}

void UOnlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    ANK_LOG("Initialize OnlineSubsystem")
    if (!OSS)
    {
        ANK_WARNING("OnlineSubsystem not found")
        return;
    }

    OSS->AddOnConnectionStatusChangedDelegate_Handle(OnConnectionStatusChangedDelegate);
    // Presence
    if (OSS->GetPresenceInterface())
    {
        OSS->GetPresenceInterface()->AddOnPresenceReceivedDelegate_Handle(OnPresenceReceivedDelegate);
    }
    else ANK_WARNING("PresenceInterface not found")
    // Session
    OSS->GetSessionInterface()->AddOnSessionInviteReceivedDelegate_Handle(OnSessionInviteReceivedDelegate);
    OSS->GetSessionInterface()->AddOnSessionParticipantsChangeDelegate_Handle(OnSessionParticipantsChangeDelegate);

    OSS->GetSessionInterface()->AddOnRegisterPlayersCompleteDelegate_Handle(OnRegisterPlayersCompleteDelegate);
    OSS->GetSessionInterface()->AddOnSessionUserInviteAcceptedDelegate_Handle(OnSessionUserInviteAcceptedDelegate);

    GetFriends();
}

void UOnlineSubsystem::OnConnectionStatusChanged(const FString& ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState,
                                                 EOnlineServerConnectionStatus::Type ConnectionState)
{
    ANK_LOG("ServiceName %s", *ServiceName)
    ANK_LOG("ConnectionState %d", (int)ConnectionState)
}

void UOnlineSubsystem::OnPresenceReceived(const FUniqueNetId& UserId, const TSharedRef<FOnlineUserPresence>& Presence)
{
    ANK_LOG("OnPresenceReceived")
    FANKOnlineFriend User;
    User.Id = UserId.ToString();
    User.Name = OSS->GetFriendsInterface()->GetFriend(0, UserId, "")->GetDisplayName();
    User.bIsPlaying = Presence->bIsPlaying;
    User.bIsPlayingThisGame = Presence->bIsPlayingThisGame;
    User.State = (decltype(User.State))(int)Presence->Status.State;
    BP_OnPresenceUpdateDelegate.Broadcast(User);
}

void UOnlineSubsystem::OnCreateSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    OSS->GetSessionInterface()->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);
    ANK_LOG("session created")
    BP_OnCreateSessionDelegate.Broadcast(SessionName, bWasSuccessful);
}

void UOnlineSubsystem::OnDestroySessionCompleted(FName SessionName, bool bWasSuccessful)
{
    BP_OnDestroySessionCompleteDelegate.Broadcast(SessionName, bWasSuccessful);
}

void UOnlineSubsystem::OnJoinSessionCompleted(FName SessionName, EOnJoinSessionCompleteResult::Type JoinResult)
{
    if (JoinResult != EOnJoinSessionCompleteResult::Type::Success)
    {
        ANK_ERROR("OnJoinSessionCompleted error %s %d", *SessionName.ToString(), JoinResult)
    }
    ANK_LOG("OnJoinSessionCompleted %s %d", *SessionName.ToString(), JoinResult)
    BP_OnJoinSessionCompleteDelegate.Broadcast(SessionName);

    FString URL;
    IOnlineSessionPtr Session = OSS->GetSessionInterface();
    if (Session.IsValid() && Session->GetResolvedConnectString(SessionName, URL))
    {
        APlayerController* PC = GetWorld()->GetFirstPlayerController();
        if (PC)
        {
            PC->ClientTravel(URL, TRAVEL_Absolute);
        }
    }
}

void UOnlineSubsystem::OnRegisterPlayersCompleted(FName SessionName, const TArray<TSharedRef<const FUniqueNetId>>& Players, bool bWasSuccessful)
{
    ANK_LOG("OnRegisterPlayersCompleted %s %d", *SessionName.ToString(), bWasSuccessful)
}

void UOnlineSubsystem::OnSessionInviteReceived(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId,
                                               const FOnlineSessionSearchResult& InviteResult)
{
    ANK_LOG("OnSessionInviteReceived received %s %s", *UserId.ToString(), *FromId.ToString())
}

void UOnlineSubsystem::OnSessionParticipantsUpdated(FName SessionName, const FUniqueNetId& UserId, bool JoinLeave)
{
    ANK_LOG("OnSessionParticipantsUpdated received %s %s %d", *SessionName.ToString(), *UserId.ToDebugString(), JoinLeave)
    auto UserName = OSS->GetFriendsInterface()->GetFriend(0, UserId, "")->GetDisplayName();
    BP_OnSessionParticipantsUpdateDelegate.Broadcast(UserId.ToString(), UserName, JoinLeave);
    //OSS->GetSessionInterface()->GetNamedSession("ANK TEST")->RegisteredPlayers
}

void UOnlineSubsystem::OnSessionUserInviteAccepted(const bool bWasSuccessful, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId,
                                                   const FOnlineSessionSearchResult& InviteResult)
{
    ANK_LOG("OnSessionUserInviteAccepted %d", bWasSuccessful)
    OSS->GetSessionInterface()->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);
    OSS->GetSessionInterface()->JoinSession(ControllerId, "ANK TEST", InviteResult);
}

void UOnlineSubsystem::OnStartSessionCompleted(FName SessionName, bool bWasSuccessful)
{
    BP_OnStartSessionCompleteDelegate.Broadcast(SessionName, bWasSuccessful);
    auto PlayersCount = GetWorld()->GetNumPlayerControllers();
}

void UOnlineSubsystem::OnFriendsChanged()
{
    ANK_LOG("friends update")
    //OSS->GetSessionInterface()->GetNamedSession("ANK TEST")->RegisteredPlayers
}

void UOnlineSubsystem::OnReadFriendsListCompleted(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr)
{
    TArray<TSharedRef<FOnlineFriend>> Result;
    if (!bWasSuccessful) ANK_ERROR("ReadFriendList failed: %s", *ErrorStr)

    bool GetOk = OSS->GetFriendsInterface()->GetFriendsList(LocalUserNum, ListName, Result);
    /*
    TArray<FANKOnlineFriend> BPResult;
    for (auto Friend : Result)
    {
        FANKOnlineFriend ANKFriend;
        ANKFriend.Name = Friend->GetDisplayName();
        BPResult.Add(ANKFriend);
    }
    BPResult.Add(FANKOnlineFriend{ "test" });*/

    struct Sorting
    {
        Sorting(TArray<TSharedRef<FOnlineFriend>> Result) {}
        bool operator()(TSharedRef<FOnlineFriend> A, TSharedRef<FOnlineFriend> B) const
        {
            return A->GetPresence().bIsPlayingThisGame && !B->GetPresence().bIsPlaying
            || A->GetPresence().bIsPlaying && !B->GetPresence().bIsPlaying
            || A->GetPresence().Status.State == EOnlinePresenceState::Online && B->GetPresence().Status.State != EOnlinePresenceState::Online
            || A->GetPresence().Status.State == EOnlinePresenceState::DoNotDisturb && B->GetPresence().Status.State != EOnlinePresenceState::DoNotDisturb
            || A->GetPresence().Status.State == EOnlinePresenceState::Away && B->GetPresence().Status.State != EOnlinePresenceState::Away
            ;
        }
    };

    Result.Sort(Sorting(Result));

    OnFriendListCompleteDelegate.Broadcast(Result);
}