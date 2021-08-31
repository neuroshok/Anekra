#include "Anekra/Player/ANKPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "ANKHUD.h"
#include "ANKPlayerState.h"
#include "Ability/Binding.h"
#include "Ability/Freeze.h"
#include "Net/UnrealNetwork.h"
#include "Anekra/Log.h"
#include "Anekra/Game/Constant.h"

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

    int BindIndex = static_cast<int32>(EBinding::Ability1);
    int SlotIndex = 0;
    for (SlotIndex = 0; SlotIndex < Abilities.Num(); ++SlotIndex)
    {
        if (Abilities[SlotIndex] == EAbilityType::None)
        {
            Abilities[SlotIndex] = AbilityID;
            BindIndex += SlotIndex;
            ++AbilityCount;
            break;
        }
    }

    const FGameplayAbilitySpec AbilitySpec{ AbilityClass, 1, BindIndex };

    FGameplayAbilitySpecHandle Handle = GetPlayerState<AANKPlayerState>()->GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
    Slots.Add(Handle, SlotIndex);

    OnAbilitiesUpdated();
}

// server
void AANKPlayerController::RemoveAbility(FGameplayAbilitySpecHandle Handle)
{
    if (GetLocalRole() == ROLE_Authority)
    {
        int Slot = 0;
        Slots.RemoveAndCopyValue(Handle, Slot);
        check(Slot < Abilities.Num());

        Abilities[Slot] = EAbilityType::None;
        --AbilityCount;
        OnAbilitiesUpdated();
    }
}

void AANKPlayerController::NotifyError(FString Message)
{
    Cast<AANKHUD>(GetHUD())->Error(std::move(Message));
}

void AANKPlayerController::BeginPlay()
{
    Super::BeginPlay();
    Abilities.SetNum(Game.Player.AbilitiesCount);
    for (auto& Ability : Abilities)
    {
        Ability = EAbilityType::None;
    }
    AbilityCount = 0;
}

void AANKPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AANKPlayerController, Abilities);
}

// server
void AANKPlayerController::Unlock()
{
    if (GetLocalRole() == ROLE_Authority)
    {
        auto AbilityID = FMath::RandRange(0, static_cast<int8>(EAbilityType::Count) - 1);
        AddAbility(static_cast<EAbilityType>(AbilityID));
    }
}

void AANKPlayerController::OnAbilitiesUpdated()
{
    OnAbilitiesUpdateDelegate.Broadcast();
}