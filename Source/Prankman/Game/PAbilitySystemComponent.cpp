#include "PAbilitySystemComponent.h"

#include "Prankman/log.h"

void UPAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo)
{
    if (BoundAbilities || !InputComponent) return;
    Super::BindAbilityActivationToInputComponent(InputComponent, BindInfo);
    BoundAbilities = true;
}