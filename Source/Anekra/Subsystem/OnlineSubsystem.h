#pragma once

#include "Interfaces/OnlineSessionInterface.h"

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSubsystem.generated.h"


UCLASS()
class ANEKRA_API UOnlineSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnConnectionStatusChanged, const FString& /*ServiceName*/, EOnlineServerConnectionStatus::Type /*LastConnectionState*/, EOnlineServerConnectionStatus::Type /*ConnectionState*/);
    typedef FOnConnectionStatusChanged::FDelegate FOnConnectionStatusChangedDelegate;

public:
    UFUNCTION(BlueprintCallable, Category = "Anekra|Online|Session")
    void CreateSession();

    UFUNCTION(BlueprintCallable, Category = "Anekra|Online")
    FString GetUserName() const;

    TArray<TSharedRef<FOnlineFriend>> GetFriends() const;

    void OnConnectionStatusChanged(const FString& ServiceName, EOnlineServerConnectionStatus::Type LastConnectionState, EOnlineServerConnectionStatus::Type ConnectionState);
    void OnCreateSessionCompleted(FName SessionName, bool Successful);

protected:
    UOnlineSubsystem();
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
    FOnConnectionStatusChangedDelegate OnConnectionStatusChangedDelegate;
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

    FDelegateHandle CreateSessionCompleteDelegateHandle;

    class IOnlineSubsystem* OSS = nullptr;
    TSharedPtr<FOnlineSessionSettings> Settings;
};