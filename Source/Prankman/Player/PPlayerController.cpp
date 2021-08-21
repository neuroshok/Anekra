#include "Prankman/Player/PPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "PHUD.h"
#include "PPlayerState.h"
#include "Ability/PBinding.h"
#include "Ability/PFreeze.h"
#include "Net/UnrealNetwork.h"
#include "Prankman/log.h"

void APPlayerController::InitializeHUD()
{
    /*
    if (GetHUD() || !IsLocalPlayerController()) return;
    SpawnDefaultHUD();
    Cast<APHUD>(GetHUD())->Initialize();*/
}

// server
void APPlayerController::AddAbility(EPAbilityType AbilityID)
{
    check(GetLocalRole() == ROLE_Authority);

    TSubclassOf<UGameplayAbility> AbilityClass;

    switch (AbilityID)
    {
        case EPAbilityType::Freeze: AbilityClass = UPFreezeAbility::StaticClass(); break;
        case EPAbilityType::CrossFire: AbilityClass = UPFreezeAbility::StaticClass(); break;
    }
    check(AbilityClass);

    FGameplayAbilitySpec AbilitySpec{ AbilityClass, 1, static_cast<int32>(EPBinding::Ability1) };
    GetPlayerState<APPlayerState>()->GetAbilitySystemComponent()->GiveAbility(AbilitySpec);

    PM_LOG("AddAbility")
    Abilities.Add(AbilityID);
    OnAbilitiesUpdated();
}

void APPlayerController::NotifyError(FString Message)
{
    Cast<APHUD>(GetHUD())->Error(std::move(Message));
}

void APPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void APPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APPlayerController, Abilities);
}

// server
void APPlayerController::Unlock()
{
    PM_LOG("Unlock")
    check(GetLocalRole() == ROLE_Authority);
    auto AbilityID = FMath::RandRange(0, static_cast<int8>(EPAbilityType::Count) - 1);
    AddAbility(static_cast<EPAbilityType>(AbilityID));
}

void APPlayerController::OnAbilitiesUpdated()
{
    OnAbilitiesUpdateDelegate.Broadcast();
}