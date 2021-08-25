#include "Anekra/Player/ANKPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "ANKHUD.h"
#include "ANKPlayerState.h"
#include "Ability/Binding.h"
#include "Ability/Freeze.h"
#include "Net/UnrealNetwork.h"
#include "Anekra/Log.h"

void AANKPlayerController::InitializeHUD()
{
    /*
    if (GetHUD() || !IsLocalPlayerController()) return;
    SpawnDefaultHUD();
    Cast<AANKHUD>(GetHUD())->Initialize();*/
}

// server
void AANKPlayerController::AddAbility(EAbilityType AbilityID)
{
    check(GetLocalRole() == ROLE_Authority);

    TSubclassOf<UGameplayAbility> AbilityClass;

    switch (AbilityID)
    {
        case EAbilityType::Freeze: AbilityClass = UFreezeAbility::StaticClass(); break;
        case EAbilityType::CrossFire: AbilityClass = UFreezeAbility::StaticClass(); break;
    }
    check(AbilityClass);

    FGameplayAbilitySpec AbilitySpec{ AbilityClass, 1, static_cast<int32>(EBinding::Ability1) };
    GetPlayerState<AANKPlayerState>()->GetAbilitySystemComponent()->GiveAbility(AbilitySpec);

    ANK_LOG("AddAbility")
    Abilities.Add(AbilityID);
    OnAbilitiesUpdated();
}

void AANKPlayerController::NotifyError(FString Message)
{
    Cast<AANKHUD>(GetHUD())->Error(std::move(Message));
}

void AANKPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void AANKPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AANKPlayerController, Abilities);
}

// server
void AANKPlayerController::Unlock()
{
    ANK_LOG("Unlock")
    check(GetLocalRole() == ROLE_Authority);
    auto AbilityID = FMath::RandRange(0, static_cast<int8>(EAbilityType::Count) - 1);
    AddAbility(static_cast<EAbilityType>(AbilityID));
}

void AANKPlayerController::OnAbilitiesUpdated()
{
    OnAbilitiesUpdateDelegate.Broadcast();
}