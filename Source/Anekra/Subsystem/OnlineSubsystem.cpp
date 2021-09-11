#include "Anekra/Subsystem/OnlineSubsystem.h"

#include "OnlineSubsystemUtils.h"
#include "Anekra/Log.h"
#include "GameFramework/GameUserSettings.h"

void UOnlineSubsystem::CreateSession()
{
    OSS->GetSessionInterface()->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

    Settings = MakeShareable(new FOnlineSessionSettings);
    Settings->NumPrivateConnections = 0;
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
    Settings->Set(SETTING_MAPNAME, FString("Your Level Name"), EOnlineDataAdvertisementType::ViaOnlineService);

    CreateSessionCompleteDelegateHandle = OSS->GetSessionInterface()->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);
    bool Status = OSS->GetSessionInterface()->CreateSession(0, "test", *Settings);
    if (!Status) ANK_ERROR("CreateSession failed")
}

FString UOnlineSubsystem::GetUserName() const
{
    return *OSS->GetIdentityInterface()->GetPlayerNickname(0);
}

TArray<TSharedRef<FOnlineFriend>> UOnlineSubsystem::GetFriends() const
{
    TArray<TSharedRef<FOnlineFriend>> Out;
    auto Status = OSS->GetFriendsInterface()->GetFriendsList(0, "", Out);
    if (!Status) ANK_LOG("ERROR FL")
    ANK_LOG("____%d", Out.Num())
    return Out;
}

void UOnlineSubsystem::OnConnectionStatusChanged(const FString& ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState,
EOnlineServerConnectionStatus::Type ConnectionState)
{
    ANK_LOG("ServiceName %s", *ServiceName)
    ANK_LOG("ConnectionState %d", (int)ConnectionState)
}

void UOnlineSubsystem::OnCreateSessionCompleted(FName SessionName, bool Successful)
{
    ANK_LOG("session created")
    OSS->GetSessionInterface()->StartSession("test");
}

UOnlineSubsystem::UOnlineSubsystem()
    : OnConnectionStatusChangedDelegate(FOnConnectionStatusChangedDelegate::CreateUObject(this, &UOnlineSubsystem::OnConnectionStatusChanged))
    , OnCreateSessionCompleteDelegate(FOnCreateSessionCompleteDelegate::CreateUObject(this, &UOnlineSubsystem::OnCreateSessionCompleted))
{
    OSS = IOnlineSubsystem::Get(STEAM_SUBSYSTEM);
    if (!OSS) OSS = IOnlineSubsystem::Get(NULL_SUBSYSTEM);
}

void UOnlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    if (!OSS)
    {
        ANK_WARNING("OnlineSubsystem not found")
        return;
    }

    OSS->AddOnConnectionStatusChangedDelegate_Handle(OnConnectionStatusChangedDelegate);
}