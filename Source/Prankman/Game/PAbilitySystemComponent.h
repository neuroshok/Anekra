#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/Object.h"
#include "PAbilitySystemComponent.generated.h"

UCLASS()
class PRANKMAN_API UPAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo) override;

    virtual void InternalServerTryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool InputPressed, const FPredictionKey& PredictionKey, const FGameplayEventData* TriggerEventData) override;

private:
    bool BoundAbilities = false;
};