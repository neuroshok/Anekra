#include "PAbilitySystemComponent.h"

void UPAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo)
{
    if (BoundAbilities || !InputComponent) return;
    Super::BindAbilityActivationToInputComponent(InputComponent, BindInfo);
    BoundAbilities = true;
}