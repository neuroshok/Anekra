#include "Anekra/Player/ANKPlayerController.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "ANKHUD.h"
#include "ANKPlayerState.h"
#include "Ability/Binding.h"
#include "Net/UnrealNetwork.h"
#include "Anekra/Game/ANKGameInstance.h"
#include "Anekra/Game/Constant.h"

void AANKPlayerController::InitializeHUD()
{
    /*
    if (GetHUD() || !IsLocalPlayerController()) return;
    SpawnDefaultHUD();
    Cast<AANKHUD>(GetHUD())->Initialize();*/
}

// server
void AANKPlayerController::AddAbility(int AbilityID)
{
    check(GetLocalRole() == ROLE_Authority);

    TSubclassOf<UGameplayAbility> AbilityClass = Cast<UANKGameInstance>(GetGameInstance())->GetAbilityClass(AbilityID);

    int BindIndex = static_cast<int32>(EBinding::Ability1);
    int SlotIndex;
    for (SlotIndex = 0; SlotIndex < Abilities.Num(); ++SlotIndex)
    {
        if (Abilities[SlotIndex] == -1)
        {
            Abilities[SlotIndex] = AbilityID;
            BindIndex += SlotIndex;
            ++AbilitiesCount;
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

        Abilities[Slot] = -1;
        --AbilitiesCount;
        OnAbilitiesUpdated();
    }
}

void AANKPlayerController::NotifyError(FString Message)
{
    if (!GetHUD()) return;
    Cast<AANKHUD>(GetHUD())->Error(std::move(Message));
}

void AANKPlayerController::BeginPlay()
{
    Super::BeginPlay();
    Abilities.SetNum(AbilitiesCountMax);
    for (auto& Ability : Abilities) Ability = -1;
    AbilitiesCount = 0;
    OnAbilitiesUpdated();
}

void AANKPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AANKPlayerController, Abilities);
    DOREPLIFETIME(AANKPlayerController, AbilitiesCount);
}

// server
void AANKPlayerController::Unlock()
{
    if (GetLocalRole() == ROLE_Authority)
    {
        auto AbilityID = FMath::RandRange(0, Cast<UANKGameInstance>(GetGameInstance())->GetAbilityAsset()->Abilities.Num() - 1);
        AddAbility(AbilityID);
    }
}

void AANKPlayerController::OnAbilitiesUpdated()
{
    OnAbilitiesUpdateDelegate.Broadcast();
}