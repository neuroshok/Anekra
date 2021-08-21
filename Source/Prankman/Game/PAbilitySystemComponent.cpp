#include "PAbilitySystemComponent.h"

#include "Prankman/log.h"

void UPAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo)
{
    if (BoundAbilities || !InputComponent) return;
    Super::BindAbilityActivationToInputComponent(InputComponent, BindInfo);
    BoundAbilities = true;
}

void UPAbilitySystemComponent::InternalServerTryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool bInputPressed,
const FPredictionKey& PredictionKey, const FGameplayEventData* TriggerEventData)
{
    PM_LOG("activate ab")
    Super::InternalServerTryActivateAbility(AbilityToActivate, bInputPressed, PredictionKey, TriggerEventData);
}